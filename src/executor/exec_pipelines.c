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
*/
int		create_pipes(t_state *shell)
{
	int		n_pipes;
	int		i;

	n_pipes = shell->pid_count - 1;
	while (i < n_pipes)
	{
		if (pipe(shell->pipe_fds))
			return (ERROR_PIPELINE);
	}
	return (SUCCESS);
}

/*
Goin on a hunch, there might have to be a recursive spawn_and_run function,
which spawns, and then runs and outputs, between each fork-pair individually, 
in sequence, before moving to next fork-pair.
In that logic, create_pipes makes ALL the pipes BEFORE ANY of the pairs are forked.
The below spawn_children just iteratively creates all forks rn, in one go.
*/
int		spawn_and_run(t_state *shell, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < shell->pid_count)
	{
		if (fork_child(shell->pids[i], shell))
			return (ERROR_FORKING);
		i++;
	}
	postorder_traversal();
	return (SUCCESS);
}

//redirections are processed before the next pipe connection.
int		run_pipeline();
{
	int		status;

	child_pid = fork();
	if (child_pid == -1)
	{
		shell_state->exit_status = ERROR_PIPELINE;
		return (ERROR_PIPELINE);
	}
	else if (child_pid == 0)
	{
		if (is_builtin(cmd->cmd))
			exec_builtin(cmd, shell_state);
		else
			exec_extern(cmd, shell_state);
		exit(shell_state->exit_status);
	}
	wait_pid(child_pid, &status, 0);
	if (WIFEXITED(status))
		shell_state->exit_status = WEXITSTATUS(status);
	return (shell_state->exit_status);
}

int		close_pipes()
{
	close();
	return (SUCCESS);
}
