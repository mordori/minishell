/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:09:55 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/12 16:33:18 by jvalkama         ###   ########.fr       */
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

void	execute_simple(t_cmd *cmd, t_state *shell_state) 
{
	if (is_builtin(cmd->cmd))
		exec_builtin(cmd, shell_state);
	else
		exec_extern(cmd, shell_state);
}

//need a loop/recursion to execute the cmds in order when pipeline
void	execute_pipeline(t_cmd **cmd, t_state *shell_state)
{
	bool		is_builtin;

	is_builtin = is_builtin(); //no forks if builtin
	create_pipes(shell_state); //the loop or recursion should break with error ofc.
	spawn_children(shell_state);
	close_pipes(shell_state);
}
