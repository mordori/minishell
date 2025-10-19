/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:09:55 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/19 05:00:37 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "io.h"

//NOTE: NODE CREATION HAPPENS IN INIT_NODES() WHICH IS CALLED IN MAIN.
//FIX: define init_nodes() in inits.c

int	executor(t_minishell *ms)
{
	command_verification(ms); //NOTE: look into moving this deeper. reason: commands could be verified where they're accessed, e.g. within the loop.
	if (ms->state.mode == SIMPLE)
		execute_simple(ms);
	else if (ms->state.mode == PIPELINE)
		execute_pipeline(ms);
	return(SUCCESS);
}

//NOTE: ms is needed at least by the builtin export, if it triggers 'invalid identificator' -error

void	execute_simple(t_minishell *ms)
{
	pid_t	child_pid;
	int		status;

	if (ms->node->pipe_fds[0] == ERROR || ms->node->pipe_fds[1] == ERROR)
		return ;
	if (ms->node->cmd.builtin)
		exec_builtin(ms);
	else
	{
		if (fork_child(&child_pid))
			warning(ms, NULL);
		if (child_pid == 0)
		{
			dup_io(ms->node);
			exec_extern(ms);
		}
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
		{
			ms->state.exit_status = WEXITSTATUS(status);
			if (ms->state.exit_status)
				warning(ms, NULL);
		}
	} //katotaan mita on in ja out ja sitten luetaan/kirjoitetaan
}

void	execute_pipeline(t_minishell *ms)
{
	int	prev_fd;
	int	count;

	count = 0;
	prev_fd = -1;
	while (ms->node)
	{
		if (ms->node->pipe_fds[0] != ERROR && ms->node->pipe_fds[1] != ERROR)
		{
			ms->state.exit_status = spawn_and_run(ms, count, &prev_fd);
			if (ms->state.exit_status)
				warning(ms, NULL);
		}
		ms->node = ms->node->next;
		count++;
	}
	if (wait_pids(&ms->state))
		warning(ms, NULL);
}

int	wait_pids(t_state *state)
{
	int	status;
	int	i;

	i = 0;
	while (i < state->child_count)
	{
		waitpid(state->pids[i], &status, 0); //FIX: declaration from sys/types.h in defines.h doesnt seem to reach here. so There's also sys/wait.h in executor.h now.
		if (WIFEXITED(status))
			state->exit_status = WEXITSTATUS(status);
		if (state->exit_status)
			return (state->exit_status);
		i++;
	}
	return (SUCCESS);
}
