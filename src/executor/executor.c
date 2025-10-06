/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:09:55 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/06 03:06:22 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//SOME OF THESE PARAS DO DEPEND ON PARSER OUTPUT. so, SUBJECT TO CHANGE.
//NODE CREATION CAN HAPPEN HERE BASED ON TOKENS for example.

int	executor(t_minishell *ms)
{
	t_state		*state;

	state = ms->state;
	if (state->mode == SIMPLE)
		execute_simple(ms->node, state);
	else if (state->mode == PIPELINE)
		execute_pipeline(ms->node, state);
	if (state->exit_status)
		clean_reset(ms->node, state);
	//cleaning old node and state?
	return(state->exit_status);
}

int	execute_simple(t_node *node, t_state *shell)
{
	pid_t		child_pid;
	int			status;

	if (is_builtin(cmd->cmd))
		exec_builtin(cmd, shell);
	else
	{
		if (fork_child(&child_pid, shell))
			return (ERROR_FORKING);
		if (child_pid == 0)
			exec_extern(cmd, shell);
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
	return (shell->exit_status);
}

int	execute_pipeline(t_node *node, t_state *shell)
{
	bool		is_builtin;
	int			prev_fd;
	int			count;

	count = 0;
	prev_fd = -1;
	while (node)
	{
		shell->exit_status = spawn_and_run(node, shell, count, &prev_fd);
		if (shell->exit_status)
			return (shell->exit_status);
		node = node->next;
		count++;
	}
	wait_pids(node, shell);
	return (shell->exit_status);
}
