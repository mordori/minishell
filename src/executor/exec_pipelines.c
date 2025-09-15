/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipelines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/15 17:35:04 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
 * The ROUGH GIST OF THINGS:
 * pipeline logic. basically PIPEX shit, calld from execute_pipeline in executor.c
 * basically, each pipeline "cmd" is a pipe with a left and a right cmd, 
 * i.e. two commands connected by one pipe.
 * Each pipeline command requires two forks (two PIDs) and one pipe (two fildes),
 * where the PIDs are matched with their respective fildes somehow.
 * But for each consecutive cmd in the pipeline, its left and the previous right overlap
 * There are as many forks (PIDs) as cmds in the pipeline, 
 * and the amount of pipes connecting the PIDs is forks-1.
 * the right cmd in the previous pipe needs to be the left in the next pipe, passing its output on til the end
*/
int		create_pipes(t_state *shell)
{
	int		n_pipes;
	int		i;

	n_pipes = shell->pid_count - 1;
	while (i < n_pipes)
	{
		if (pipe(shell->pipe_fds))
			return (ERROR_PIPELINE); //temp error code
	}
	return (SUCCESS);
}

int		spawn_children(t_state *shell, t_cmd *cmd)
{
	pid_t		child_pid1;
	pid_t		child_pid2;

	child_pid1 = fork();
	if (child_pid1 == -1)
	{
		shell->exit_code = ERROR_PIPELINE;
		return (ERROR_PIPELINE);
	}
	child_pid2 = fork();
	if (child_pid2 == -1)
	{
		shell->exit_code = ERROR_PIPELINE;
		return (ERROR_PIPELINE);
	}
	shell->pid[]
	return (SUCCESS);
}

//below func was in simple executor, 
//but moved it here for reference (instead of deleting),
//since forking was unnecessary in simple executor,
//but this kind of shit is needed here.
int		child_runs();
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
