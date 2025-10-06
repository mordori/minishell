/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:58:00 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/25 15:02:08 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

void	wait_pids(t_cmd *cmd, t_shell *shell)
{
	int		status;

	while (i < shell->pid_count)
	{
		wait_pid(shell->pids[i], &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		if (shell->exit_status)
			return (shell->exit_status); // if error, should close *everything*, and probably return some msg.
		i++;
	}
}

// parrsin dont know whther cmd is a valid one, it just tokenizes and so on.
// so, here a bunch of stuff needs to be done:

void	command_verification()
{
	//FIX: This is important to do soon:
	// 1. Check if command is BUILTIN, and designate it in cmd->builtin.
	// 2. Verify command exists, and fetch/parse the full path to the command
	// 		3. insert full path in cmd->cmd
	//
}
