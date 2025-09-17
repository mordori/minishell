/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:09:55 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/16 16:00:05 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include ""

//SOME OF THESE PARAS DO DEPEND ON PARSER OUTPUT. so, SUBJECT TO CHANGE.

int	cmd_executor(t_cmd **cmd, t_state *shell_state)
{
	t_cmd		command;

	command = *cmd; 
	if (command->type == SIMPLE)
		execute_simple(command, shell_state);
	else if (command->type == PIPELINE)
		execute_pipeline(cmd, shell_state);
	return(shell_state->exit_status);
}

int	execute_simple(t_cmd *cmd, t_state *shell_state) 
{
	pid_t		child_pid;
	int			status;

	if (is_builtin(cmd->cmd))
		exec_builtin(cmd, shell_state);
	else
	{
		if (fork_child(&child_pid, shell_state))
			return (ERROR_FORKING);
		if (child_pid == 0)
			exec_extern(cmd, shell_state);
		wait_pid(child_pid, &status, 0);
		if (WIFEXITED(status))
			shell_state->exit_status = WEXITSTATUS(status);
	}
	return (shell_state->exit_status);
}

/*
WIP. need a loop/recursion to execute the cmds in order when pipeline
the loop or recursion should break with error ofc.

pipeline technically needs no forks for the cmds that are builtin, 
but just forking everything might simplify the process flow.
*/
int	execute_pipeline(t_cmd **cmd, t_state *shell_state)
{
	bool		is_builtin;

	is_builtin = is_builtin();
	create_pipes(cmd, shell_state);
	spawn_and_run(cmd, shell_state);
	close_pipes(shell_state);
	return (shell_state->exit_status);
}

int	exec_builtin(t_cmd *cmd, t_state *shell_state)
{
	cmd_func	*dispatch_table[7];

	dispatch_table = {echo, cd, pwd, export, unset, env, exit};
	return (dispatch_table[cmd->builtin_cmd](cmd, shell_state));
}
