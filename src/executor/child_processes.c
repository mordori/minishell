/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:41:25 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/22 18:29:02 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	run_node(t_node *node, t_shell *shell)
{
	run_pipeline_cmd(cmd, shell);
}

/*
* I think each child process needs a read FD and a write FD (pipe's read-end and write-end),
* and the write FD is the read FD for the next child process.
* But the first node prolly reads from the parent data (not read end),
* and the last node outputs in stdout (not write end).
*/
void	run_pipeline_cmd(t_cmd *cmd, t_state *shell)
{
	if (cmd->builtin))
		exec_builtin(cmd, shell_state);
	else
		exec_extern(cmd, shell_state);
	exit(shell_state->exit_status);
}

clean_exit()
{
	// invoke in CHILD ALSO
	//take memory arena
	free();
	exit();
}
