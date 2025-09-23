/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:58:00 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/22 18:29:01 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "executor.h"

bool	is_builtin(t_cmd *command) //the parameter/member format depends on parser output
{
	return (command->builtin_cmd == ECHO
		|| command->builtin_cmd == CD
		|| command->builtin_cmd == PWD
		|| command->builtin_cmd == EXPORT
		|| command->builtin_cmd == UNSET
		|| command->builtin_cmd == ENV
		|| command->builtin_cmd == EXIT);
}

void	wait_pids(t_cmd *cmd, t_shell *shell)
{
	int		status;

	while (i < shell->pid_count)
	{
		wait_pid(shell->pids[i], &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		if (shell->exit_status)
			; // if error, should close *everything*, and probably return some msg.
		i++;
	}
}
