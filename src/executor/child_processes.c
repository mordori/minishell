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

//redirections are processed before the next pipe connection!

void	run_node(t_node *node, t_shell *shell, int i)
{
	int		needed_pps;

	if (i == 0) //guess each node has to close each unused pipe_fd in all the linked structs.
	{
		needed_pps = 1;
		close(1);
		dup2(node->pipe_fds[needed_pps], STDOUT_FILENO);
		close_pipes(node, needed_pps);
	}
	else if (i == shell->child_count - 1)
	{
		needed_pps = 0;
		close(0);
		dup2(node->pipe_fds[needed_pps], STDIN_FILENO);
		close_pipes(node, needed_pps);
	}
	else
	{
		needed_pps = 2;
		dup2(node->pipe_fds[0], STDIN_FILENO);
		dup2(node->pipe_fds[1], STDOUT_FILENO);
		close_pipes(node, needed_pps);
	}
	//close the used up pipes. All need to be closed.
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
