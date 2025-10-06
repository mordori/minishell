/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:09:55 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/06 17:26:35 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//NOTE: NODE CREATION HAPPENS IN INIT_NODES() WHICH IS CALLED IN MAIN.
//FIX: define init_nodes() in inits.c

int	executor(t_minishell *ms)
{
	t_state		*state;

	state = ms->state;
	command_verification(ms); //FIX: define command_verification() in executor_utils.c
	if (state->mode == SIMPLE)
		execute_simple(ms);
	else if (state->mode == PIPELINE)
		execute_pipeline(ms);
	if (state->exit_status)
		clean_reset(ms);
	return(state->exit_status);
}

//NOTE: ms is needed at least by the builtin export, if it triggers 'invalid identificator' -error

int	execute_simple(t_minishell *ms)
{
	pid_t		child_pid;
	int			status;

	if (is_builtin(cmd->cmd))
		exec_builtin(cmd, state);
	else
	{
		if (fork_child(&child_pid, state))
			return (ERROR_FORKING);
		if (child_pid == 0)
			exec_extern(cmd, state);
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			state->exit_status = WEXITSTATUS(status);
	}
	return (state->exit_status);
}

int	execute_pipeline(t_minishell *ms)
{
	bool		is_builtin;
	int			prev_fd;
	int			count;

	count = 0;
	prev_fd = -1;
	while (node)
	{
		state->exit_status = spawn_and_run(node, state, count, &prev_fd);
		if (state->exit_status)
			return (state->exit_status);
		node = node->next;
		count++;
	}
	wait_pids(node, state);
	return (state->exit_status);
}
