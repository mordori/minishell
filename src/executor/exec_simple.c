/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:39 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/12 16:46:25 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "executor.h"

// gonna make a dispatch table with a function pointer array.
void	exec_builtin(t_cmd *cmd, t_state *shell_state)
{
	cd();
	echo();
	pwd();
	env();
	exit();
	export();
	unset();
	return ;
}

void	exec_extern(t_cmd *cmd, t_state *shell_state)
{
	char		*command;
	char		**args;

	command = cmd->args[0];
	args = cmd->args + 1;
	execve(command[0], args);
	return ;
}
