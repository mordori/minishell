/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/27 12:50:12 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//due to fork(), both parent and child initially share
//the same heap (via COW), but each is responsible for its own cleanup.
//The key insight is: free() in the child does not free memory
//from the parent, and vice versa.

static void	try_pipe(t_minishell *ms, t_node *node);
static void	io_directions(t_minishell *ms, t_node *node, int prev_read);
static void	close_parent_pps(t_node *node, int *prev_read);

int	spawn_and_run(t_minishell *ms, int *prev_read)
{
	pid_t		child_pid;

	child_pid = -1;
	if (ms->node->next)
		try_pipe(ms, ms->node);
	try_fork(ms, &child_pid);
	if (child_pid != 0)
	{
		if (ms->node->next)
		{
			if (close(ms->node->pipe_fds[WRITE]))
				error_exit(ms, "");
		}
	}
	if (child_pid != 0)
		ms->node->pid = child_pid;
	if (child_pid == 0)
	{
		io_directions(ms, ms->node, *prev_read);
		run_node(ms);
	}
	close_parent_pps(ms->node, prev_read);
	return (SUCCESS);
}

static void	try_pipe(t_minishell *ms, t_node *node)
{
	if (pipe(node->pipe_fds))
		error_exit(ms, "");
}

void	try_fork(t_minishell *ms, pid_t *child_pid)
{
	*child_pid = fork();
	if (*child_pid == -1)
		error_exit(ms, "");
}

static void	io_directions(t_minishell *ms, t_node *node, int prev_read)
{
	if (prev_read >= 0)
	{
		if (dup2(prev_read, STDIN_FILENO) == -1)
			error_exit(ms, "");
		close(prev_read);
	}
	else if (node->prev == NULL && prev_read >= 0)
		close(prev_read);
	if (node->next)
	{
		if (dup2(node->pipe_fds[WRITE], STDOUT_FILENO) == -1)
			error_exit(ms, "");
		close(node->pipe_fds[WRITE]);
		close(node->pipe_fds[READ]);
	}
}

static void	close_parent_pps(t_node *node, int *prev_read)
{
	if (node->prev == NULL)
		close(*prev_read);
	if (node->next)
		*prev_read = node->pipe_fds[READ];
}
