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
	//parent's custom signal handling set back to default
	if (cmd->builtin)
		error_code = exec_builtin(cmd, state);
	else
		error_code = exec_extern(cmd); //execve should clean up everything automatically
	if (error_code)		//IF WE AVOID WRITES INTO MEMORY ENTIRELY, MAYBE NO NEED TO CLEAN IN CHILD (except if parent wrote in meantime)
	{
		print_error("Pipeline command execution error.");
		error_exit();
	}
	clean_exit();  // for builtins: free anything/everything. Even FDs need to be closed according to many ppl.
}

int	exec_builtin(t_cmd *cmd, t_state *state)
{
	cmd_func	*dis_tab[8];

	dis_tab = {NULL, ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit};
	return (dis_tab[cmd->builtin_cmd](cmd, state));
}

int	exec_extern(t_cmd *cmd)
{
	char		*command;
	char		**args;

	command = get_path(cmd->cmd, get_env("PATH"));
	args = cmd->args + 1;
	execve(command, args); //execve should automatically clean up all memory, even heap
	return (errno); //return to run_node if execve failed
}
