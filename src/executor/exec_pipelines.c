/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipelines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/12 15:56:29 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
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
			return (PIPING_ERROR); //temp error code
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
		shell->exit_code = FORKING_ERROR;
		return (FORKING_ERROR);
	}
	child_pid2 = fork();
	if (child_pid2 == -1)
	{
		shell->exit_code = FORKING_ERROR;
		return (FORKING_ERROR);
	}
	shell->pid[]
	return (SUCCESS);
}

int		close_pipes()
{
	close();
	return (SUCCESS);
}
