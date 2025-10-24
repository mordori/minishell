/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipelines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/24 11:07:28 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//due to fork(), both parent and child initially share
//the same heap (via COW), but each is responsible for its own cleanup.
//The key insight is: free() in the child does not free memory
//from the parent, and vice versa.

static void	create_pipe(t_minishell *ms, t_node *node);
static void	io_directions(t_minishell *ms, t_node *node, int prev_read);
static void	close_parent_pps(t_node *node, int *prev_read);

int	spawn_and_run(t_minishell *ms, int *prev_read)
{
	pid_t		child_pid;
#ifdef DEBUG
printf("Spawn and run!\n");
printf("Current node cmd: %s\n\n", ms->node->cmd.cmd);
#endif

	child_pid = -1;
	if (ms->node->next)
		create_pipe(ms, ms->node);
#ifdef DEBUG
printf("Node %s pipe_fds: 0: %d 1: %d\n\n", ms->node->cmd.cmd, ms->node->pipe_fds[0], ms->node->pipe_fds[1]);
#endif
	fork_child(ms, &child_pid);
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
#ifdef DEBUG
printf("%s PID-%d is headed to io_directions.\n", ms->node->cmd.cmd, child_pid);
#endif
		io_directions(ms, ms->node, *prev_read);
#ifdef DEBUG
printf("%s PID-%d is headed to run_node.\n", ms->node->cmd.cmd, child_pid);
#endif
		run_node(ms);
	}
	close_parent_pps(ms->node, prev_read);
	return (SUCCESS);
}

static void	create_pipe(t_minishell *ms, t_node *node)
{
	if (pipe(node->pipe_fds))
		error_exit(ms, "");
}

void	fork_child(t_minishell *ms, pid_t *child_pid)
{
	*child_pid = fork();
	if (*child_pid == -1)
		error_exit(ms, "");
}

static void	io_directions(t_minishell *ms, t_node *node, int prev_read)
{
#ifdef DEBUG
printf("Cmd: %s is in io_directions phase.\n\n", node->cmd.cmd);
#endif
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
