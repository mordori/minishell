/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipelines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/16 16:00:03 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	spawn_and_run(t_node *node, t_state *shell, int count, int *prev_fd)
{
	pid_t		child_pid;
	
	child_pid = -1;
	if (node->next)
	{
		if (create_pipe(node, shell, prev_fd)
			return (ERROR_PIPELINE);
	}
	if (child_pid != 0 && node->cmd->builtin == false) //builtins shouldn't be forked: unset and env need to modify parent ENV vars for good
	{
		if (fork_child(&child_pid, shell))
			return (ERROR_FORKING);
		shell->pids[count] = child_pid; //this creates a copy (COW) to child of shell i think.
	}
	if (child_pid == 0)
	{
		if (redirections(node, shell, *prev_fd))
			return (ERROR_REDIR);
		run_node(node, shell, count, *prev_fd);
	}
	if (close_parent_pps(node, shell))
		return (ERROR_CLOSING_FD);
	return (SUCCESS);
}

int	fork_child(pid_t *child_pid, t_state *shell);
{
	*child_pid = fork();
	if (*child_pid == -1)
		return (ERROR_FORKING);
	return (SUCCESS);
}

int	create_pipe(t_node *node, t_state *shell, int *prev_fd)
{
	if (pipe(node->pipe_fds))
		return (ERROR_PIPELINE);
	*prev_fd = node->pipe_fds[1];
	return (SUCCESS);
}

int	redirections(t_node *node, t_state *shell, int prev_fd)
{
	if (node->prev)
	{
		if (dup2(prev_fd, STDIN_FILENO)
	  		return (ERROR_REDIR);
		if (close(prev_fd))
			return (ERROR_CLOSING_FD);
	}
	else if (node->prev == NULL)
	{
		if (close(prev_fd))
			return (ERROR_CLOSING_FD);
	}
	if (node->next)
	{
		if (dup2(node->pipe_fds[1], STDOUT_FILENO))
			return (ERROR_REDIR);
		if (close(node->pipe_fds[0]))
			return (ERROR_CLOSING_FD);
	}
	return (SUCCESS);
}

int	close_parent_pps(t_node *node, t_state *shell)
{
	if (close(node->pipe_fds[0]))
		return (ERROR_CLOSING_FD);
	if (node->prev)
	{
		if (close(node->prev->pipe_fds[1]))
			return (ERROR_CLOSING_FD);
	}
	return (SUCCESS);
}
