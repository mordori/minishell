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

//the child must call free() on heap-allocated memory 
//if it owns pointers and intends to exit cleanly — 
//but only if it accesses dynamically allocated memory. 
//	Accesses =
//
//However, due to fork(), both parent and child initially share 
//the same heap (via COW), but each is responsible for its own cleanup.
//The key insight is: free() in the child does not free memory 
//from the parent, and vice versa.

int	spawn_and_run(t_node *node, t_state *state, int count, int *prev_fd)
{
	pid_t		child_pid;
	
	child_pid = -1;
	if (node->next)
	{
		if (create_pipe(node, prev_fd)
			return (ERROR_PIPELINE);
	}
	if (child_pid != 0) //no child will ever get here since they terminate in run_node() - conditional can be changed.
	{
		if (fork_child(&child_pid))
			return (ERROR_FORKING);
		if (child_pid > 0)
			state->pids[count] = child_pid; //this creates a copy (COW) to child of shell i think.
	}
	if (child_pid == 0)
	{
		if (redirections(node, *prev_fd))
			return (ERROR_REDIR);
		run_node(node->cmd, state);
	}
	if (close_parent_pps(node))
		return (ERROR_CLOSING_FD);
	return (SUCCESS);
}

int	fork_child(pid_t *child_pid);
{
	*child_pid = fork();
	if (*child_pid == -1)
		return (ERROR_FORKING);
	return (SUCCESS);
}

int	create_pipe(t_node *node, int *prev_fd)
{
	if (pipe(node->pipe_fds))
		return (ERROR_PIPELINE);
	*prev_fd = node->pipe_fds[1];
	return (SUCCESS);
}

int	redirections(t_node *node, int prev_fd)
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

int	close_parent_pps(t_node *node)
{
	if (close(node->pipe_fds[0]))
		return (ERROR_CLOSING_FD);
	if (node->prev)
	{
		if (close(node->prev->pipe_fds[1])) // Or prev->prev ?
			return (ERROR_CLOSING_FD);
	}
	return (SUCCESS);
}
