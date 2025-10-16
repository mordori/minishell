/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:38:28 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/25 14:32:56 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	run_node(t_cmd *cmd, t_state *state)
{
	int		error_code;

	error_code = 0;
	//FIXME: parent's custom signal handling back to default
	if (cmd->builtin)
		error_code = exec_builtin(cmd, state);
	else
		error_code = exec_extern(cmd, state);
	if (error_code)		//IF WE AVOID WRITES INTO MEMORY ENTIRELY, MAYBE NO NEED TO CLEAN IN CHILD (except if parent wrote in meantime)
	{
		//print_error("Pipeline command execution error.");
		//error_exit();
		exit(ERROR); //FIXME: temp error handling
	}
	//clean_exit();  // FIXME: for builtins: free everything? Even FDs need to be closed according to many ppl.
}

void	exec_builtin(t_cmd *cmd, t_state *state)
{
	static t_funct	*dis_tab[8] = {FALSE, echo, cd, pwd, export, unset, env, exitt};

	return (dis_tab[cmd->builtin](cmd, state));
}

int	exec_extern(t_cmd *cmd, t_state *state)
{
	char		*command;
	char		**args;
	char		**envp;

	command = cmd->cmd;
	args = cmd->args + 1;
	envp = state->envp;
	execve(command, args, envp); //execve should automatically clean up all memory, even heap
	return (errno); //return to run_node if execve failed
}
