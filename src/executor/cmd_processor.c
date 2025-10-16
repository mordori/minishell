/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:38:28 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/16 16:50:51 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	run_node(t_cmd *cmd, t_state *state)
{
	//FIXME: parent's custom signal handling back to default
	if (cmd->builtin)
		exec_builtin(cmd, state);
	else
		exec_extern(cmd, state);
	//clean_exit();  // FIXME: for builtins: free everything? Even FDs need to be closed according to many ppl.
}

void	exec_builtin(t_cmd *cmd, t_state *state)
{
	static t_fun	*dt[8] = {NULL, &echo, &cd, &pwd, &export, &unset, &env, &exitt};

	return (dt[cmd->builtin](cmd, state));
}

void	exec_extern(t_cmd *cmd, t_state *state)
{
	char		*command;
	char		**args;
	char		**envp;

	command = cmd->cmd;
	args = cmd->args + 1;
	envp = state->envp;
	execve(command, args, envp); //execve should automatically clean up all memory, even heap
	if (errno) //return to run_node if execve failed
		//FIX: handle error.
		return ;
}
