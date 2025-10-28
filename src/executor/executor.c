/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:09:55 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/28 11:13:46 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	executor(t_minishell *ms)
{
	set_mode(ms);
	if (ms->state.mode == SIMPLE)
	{
		if (execute_simple(ms))
			return (ERROR_GENERAL);
	}
	else if (ms->state.mode == PIPELINE)
	{
		if(execute_pipeline(ms))
			return (ERROR_PIPELINE);
	}
	return(SUCCESS);
}

int	execute_simple(t_minishell *ms)
{
	pid_t	child_pid;
	int		status;

	if (command_verification(ms, ms->node))
		return (ERROR_CMD_NOTFOUND);
	if (ms->node->pipe_fds[0] == ERROR || ms->node->pipe_fds[1] == ERROR)
		return (ERROR);
	if (ms->node->cmd.builtin)
		return (exec_builtin(ms));
	else
	{
		try_fork(ms, &child_pid);
		if (child_pid == 0)
		{
			dup_io(ms->node);
			exec_extern(ms);
		}
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			ms->state.exit_status = WEXITSTATUS(status);
	}
	return (SUCCESS);
}

int	execute_pipeline(t_minishell *ms)
{
	int	prev_read;

	prev_read = -1;
	while (ms->node)
	{
		if (command_verification(ms, ms->node))
			return (ERROR_PIPELINE);
		if (ms->node->pipe_fds[0] != ERROR && ms->node->pipe_fds[1] != ERROR)
			ms->state.exit_status = spawn_and_run(ms, &prev_read);
		if (ms->state.exit_status)
			return (ERROR_PIPELINE);
		if (!ms->node->next)
			break;
		ms->node = ms->node->next;
	}
	node_scrollback(ms);
	if (wait_pids(ms))
		warning(ms, NULL);
	//node_scrollback(ms);
	return (SUCCESS);
}

int	wait_pids(t_minishell *ms)
{
	int	status;

	while (ms->node)
	{
		waitpid(ms->node->pid, &status, 0);
		if (WIFEXITED(status))
			ms->state.exit_status = WEXITSTATUS(status);
		if (ms->state.exit_status)
			return (ms->state.exit_status);
		ms->node = ms->node->next;
	}
	return (SUCCESS);
}

#ifdef DEBUG
//DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include <stdio.h>

int    ft_log(char *file_name, char *func_name, char *data)
{
    FILE    *fptr = fopen(file_name, "a");

    if (!fptr)
    {
        printf("Could not open log file in log-director.");
        return (0);
    }
    fprintf(fptr, \
        "In function: %s\n\nVARIABLE VALUES AT START:%s\n\n\n\n", \
        func_name, data);
    fclose(fptr);

    return (0);
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#endif
