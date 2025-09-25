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

int	exec_builtin(t_cmd *cmd, t_state *state)
{
	cmd_func	*dis_tab[8];

	dis_tab = {NULL, ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit};
	return (dis_tab[cmd->builtin_cmd](cmd, state));
}

/*
	* getenv("PATH") fetches the whole 'PATH' ENV variable, and passes it to parsing
	* for extracting the specific command path out of the PATH.
	*
	* if execve fails, the child calls exit() with exit code set to errno, 
	* which gives parent more specific info about what happened.
*/
int	exec_extern(t_cmd *cmd)
{
	char		*command;
	char		**args;

	command = get_path(cmd->cmd, get_env("PATH"));
	args = cmd->args + 1;
	execve(command, args);
	//potential cleanup requirements if any structs malloc'd and then written in after 
	exit(errno);
}
