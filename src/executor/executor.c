/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:09:55 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/18 17:49:39 by jvalkama         ###   ########.fr       */
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
int	execute_pipeline(t_cmd *cmd, t_state *shell)
{
	bool		is_builtin;
	int			n_pipes;

	n_pipes = shell->child_count;
	create_pipes(cmd, shell, n_pipes);
	spawn_and_run(cmd, shell);
	wait_pids(node, shell);
	return (shell->exit_status);
}
