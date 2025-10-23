/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipelines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/23 16:09:39 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//due to fork(), both parent and child initially share
//the same heap (via COW), but each is responsible for its own cleanup.
//The key insight is: free() in the child does not free memory
//from the parent, and vice versa.

int	spawn_and_run(t_minishell *ms, int count, int *prev_fd)
{
	pid_t		child_pid;

	
	printf("Spawn and run!\n count: %d\n prev_fd: %d\n\n", count, *prev_fd);
	printf("Current node cmd: %s\n current node pipe_fds: 0: %d 1: %d\n\n", ms->node->cmd.cmd, ms->node->pipe_fds[0], ms->node->pipe_fds[1]);

	child_pid = -1;
	if (ms->node->next)
	{
		if (create_pipe(ms->node, prev_fd))
			return (ERROR_PIPELINE);
	}
	if (child_pid != 0)
	{
		if (fork_child(&child_pid))
			return (ERROR_FORKING);
		if (child_pid > 0)
			ms->state.pids[count] = child_pid;
	}

	printf("1st PID check: %d, \n", child_pid);

	if (child_pid == 0)
	{
		if (io_directions(ms->node, *prev_fd))
			return (ERROR_REDIR);
		run_node(ms);
	}

	printf("2nd PID check: %d, \n", child_pid);

	if (close_parent_pps(ms->node)) //since everything is piped beforehand, EVERYTHING needs to be closed at appropriate times, also in each child.
		return (ERROR_PIPELINE);

	printf("\n");

	return (SUCCESS);
}

int	fork_child(pid_t *child_pid)
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

int	io_directions(t_node *node, int prev_fd)
{
	//NOTE: if in or out redir, then plug it in here somewhere
	if (node->prev)
	{
		if (dup2(prev_fd, STDIN_FILENO))
			return (ERROR_REDIR);
		if (close(prev_fd))
			return (ERROR_PIPELINE);
	}
	else if (node->prev == NULL)
	{
		if (close(prev_fd))
			return (ERROR_PIPELINE);
	}
	if (node->next)
	{
		if (dup2(node->pipe_fds[1], STDOUT_FILENO))
			return (ERROR_REDIR);
		if (close(node->pipe_fds[0]))
			return (ERROR_PIPELINE);
	}
	return (SUCCESS);
}

int	close_parent_pps(t_node *node)
{
	if (close(node->pipe_fds[0]))
		return (ERROR_PIPELINE);
	if (node->prev)
	{
		if (close(node->prev->pipe_fds[1])) // Or prev->prev ?
			return (ERROR_PIPELINE);
	}
	return (SUCCESS);
}
