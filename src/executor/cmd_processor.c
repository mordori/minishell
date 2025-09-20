/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:38:28 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/18 17:49:35 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exec_builtin(t_cmd *cmd, t_state *shell_state)
{
	cmd_func	*dispatch_table[8];

	dispatch_table = {NULL, echo, cd, pwd, export, unset, env, exit};
	return (dispatch_table[cmd->builtin_cmd](cmd, shell_state));
}

/*
	* getenv("PATH") fetches the whole 'PATH' ENV variable, and passes it to parsing
	* for extracting the specific command path out of the PATH.
	*
	* After it has executed the external command, execve() will exit the child process,
	* if it succeeds.
	* But if execve fails, the child calls exit() with exit code set to errno, 
	* which gives parent more specific info about what happened.
*/
int	exec_extern(t_cmd *cmd)
{
	char		*command;
	char		**args;

	command = parse_env(cmd->args[0], get_env("PATH"));
	args = cmd->args + 1;
	execve(command, args);
	exit(errno);
}
