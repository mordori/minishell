/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:09:55 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/09 15:45:13 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "" //muiden .c tiedostojen alaheaderit, jos tarvii

//SOME OF THESE PARAS DO DEPEND ON PARSER OUTPUT. so, SUBJECT TO CHANGE.

int	cmd_executor(t_cmd **cmd, t_state *shell_state)
{
	t_cmd		command;

	command = *cmd;
	if (command->type == SIMPLE)
		execute_simple(command, shell_state); //these are now "returning" IMPLICITLY via struct exit_status
	else if (command->type == PIPELINE)
		execute_pipeline(cmd, shell_state);
	return(shell_state->exit_status);
}

int	execute_simple(t_cmd *cmd, t_state *shell_state) //now set to return EXPLICITLY
{
	char		*command;

	command = cmd->argv[0]; //might this already be done in parsing?
	if (is_builtin(command)) //either explicit return statements for exit status (and thus error), or implicit via struct......
		return (exec_builtin(cmd, shell_state));
	return (exec_extern(cmd, shell_state)); //determin whether implici or exploicit better in wider design context a bit later.
}

int	execute_pipeline(t_cmd **cmd, t_state *shell_state)
{
	bool		is_builtin;

	is_builtin = is_builtin(); //no forks if builtin
	create_pipes(); //this needs parameters as parsed from the pipeline
	spawn_children(); //malloccaa pid:t ja forkkaa subfiles
	close_pipes();
	return (SUCCESS);
}

bool	is_builtin(command) //rly these parameters depend on parser output
{
	return (true);
	return (false);
}
