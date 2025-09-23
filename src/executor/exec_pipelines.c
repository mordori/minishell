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

/*
 * The ROUGH GIST OF THINGS:
 * pipeline logic. basically PIPEX shit, calld from execute_pipeline in executor.c
 * basically, each pipeline node is a pipe with a left and a right cmd, 
 * i.e. two commands connected by one pipe. 
 * And their output is the input for the next node,
 * which is the node above it.
 * There prolly need to be as many forks (PIDs) as cmds in the pipeline, 
 * and the amount of pipes connecting the PIDs is forks-1.
 * So let's say we have 5 cmds, that's 4 pipes = 8 file-descriptors (1 pipe = 2 file-descriptors per node)
*/
int	create_pipes(t_node *node, t_state *shell, int n_pipes)
{
	static int		i;

	if (i < n_pipes && shell->exit_status == SUCCESS)
	{
		if (pipe(node->pipe_fds))
		{
			shell->exit_status = ERROR_PIPELINE;
			return (shell->exit_status);
		}
		i++;
		create_pipes(node->next, shell, n_pipes);
	}
	i = 0;
	return (shell->exit_status);
}

/*
Goin on a hunch, there might have to be a recursive spawn_and_run function,
which spawns, and then runs and outputs, between each fork-pair individually, 
in sequence, before moving to next fork-pair.
In that logic, create_pipes makes ALL the pipes BEFORE ANY of the pairs are forked.
The below spawn_children just iteratively creates all forks rn, in one go.
*/
int	spawn_and_run(t_node *node, t_shell *shell)
{
	static pid_t	child_pid;
	static int		i;

	if (i < shell->child_count && node)
	{
		if (i == 0 || child_pid != 0)
		{
			if (fork_child(child_pid, shell))
				return (ERROR_FORKING);
			shell->pids[*i] = *child_pid;
		}
		if (child_pid == 0)
			run_node(node, shell, i);
		i++;
		spawn_and_run(node->next, shell);
	}
	i = 0;
	return (shell->exit_status);
}

/*
int	spawn_pair(pid_t *child_pid, t_state *shell, int *i)
{
	if (*i == 0 || *child_pid != 0)
	{
		if (fork_child(child_pid, shell))
			return (ERROR_FORKING);
		shell->pids[*i] = *child_pid;
	}
	if (*child_pid != 0)
	{
		*i++;
		if (fork_child(child_pid, shell))
			return (ERROR_FORKING);
		shell->pids[*i] = *child_pid;
	}
	return (SUCCESS);
}
*/

// MISSING ERROR HANDLING FOR CLOSE() FUNCTIONS.
int	close_pipes(t_node *node, int needed_pps)
{
	t_node		*tmp;

	if (needed_pps != 2)
	{
		if (needed_pps == 1)
			close(node->pipe_fds[0])
		if (needed_pps == 0)
			close(node->pipe_fds[1])
	}
	tmp = node->prev;
	while (tmp)
	{
		close(tmp->pipe_fds[0]);
		close(tmp->pipe_fds[1]);
		tmp = tmp->prev;
	}
	tmp = node->next;
	while (tmp)
	{
		close(tmp->pipe_fds[0]);
		close(tmp->pipe_fds[1]);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
