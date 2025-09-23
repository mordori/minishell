/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:09:55 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/23 16:36:25 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//SOME OF THESE PARAS DO DEPEND ON PARSER OUTPUT. so, SUBJECT TO CHANGE.

int	executor(t_node *node, t_state *shell)
{
	if (shell->mode == SIMPLE)
		execute_simple(node, shell);
	else if (shell->mode == PIPELINE)
		execute_pipeline(node, shell);
	return(shell->exit_status);
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
		wait_pid(child_pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
	return (shell->exit_status);
}

/*
WIP. need a loop/recursion to execute the cmds in order when pipeline
the loop or recursion should break with error ofc.

pipeline technically needs no forks for the cmds that are builtin,
but just forking everything might simplify the process flow.
*/
int	execute_pipeline(t_node *node, t_state *shell)
{
	bool		is_builtin;
	int			prev_fd;
	int			count;

	count = 0;
	prev_fd = -1;
	while (node)
	{
		if (spawn_and_run(node, shell, count, &prev_fd))
			return (shell->exit_status);
		node = node->next;
		count++;
	}
	wait_pids(node, shell);
	return (SUCCESS);
}
