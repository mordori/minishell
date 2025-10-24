/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:09:55 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/24 11:10:36 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	executor(t_minishell *ms)
{
	set_mode(ms);
#ifdef DEBUG
printf("Mode: %d\n\n", ms->state.mode);
#endif
	if (ms->state.mode == SIMPLE)
		execute_simple(ms);
	else if (ms->state.mode == PIPELINE)
		execute_pipeline(ms);
	return(SUCCESS);
}

void	execute_simple(t_minishell *ms)
{
	pid_t	child_pid;
	int		status;

	command_verification(ms, ms->node);
	if (ms->node->pipe_fds[0] == ERROR || ms->node->pipe_fds[1] == ERROR)
		return ;
	if (ms->node->cmd.builtin)
		exec_builtin(ms);
	else
	{
		fork_child(ms, &child_pid);
		if (child_pid == 0)
		{
			dup_io(ms->node);
			exec_extern(ms);
		}
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
		{
			ms->state.exit_status = WEXITSTATUS(status);
		}
	}
}

void	execute_pipeline(t_minishell *ms)
{
	int	prev_read;
	int	count;
#ifdef DEBUG
printf("Execute_pipeline entered.\n\n");
#endif
	count = 0;
	prev_read = -1;
	while (ms->node)
	{
		command_verification(ms, ms->node);
#ifdef DEBUG
printf("TRAVERSING pipeline loop node to node. Count: %d\n Node->cmd: %s\n Node->args[0]: %s\n\n", count, ms->node->cmd.cmd, ms->node->cmd.args[0]);
#endif
		if (ms->node->pipe_fds[0] != ERROR && ms->node->pipe_fds[1] != ERROR)
		{
			ms->state.exit_status = spawn_and_run(ms, &prev_read);
		}
		if (!ms->node->next)
			break;
		ms->node = ms->node->next;
		count++;
	}
#ifdef DEBUG
printf("Parent headed to node_scrollback.\n");
#endif
	node_scrollback(ms);
#ifdef DEBUG
printf("Parent headed to wait_pids for reaping.\n");
#endif
	if (wait_pids(ms))
		warning(ms, NULL);
}

int	wait_pids(t_minishell *ms)
{
	int	status;

#ifdef DEBUG
printf("REAPING entered.\n");
#endif
	while (ms->node)
	{
#ifdef DEBUG
printf("Reaping PID: %d.\n", ms->node->pid);
#endif
		waitpid(ms->node->pid, &status, 0);
		if (WIFEXITED(status))
			ms->state.exit_status = WEXITSTATUS(status);
#ifdef DEBUG
printf("PID-%d exited with status %d.\n", ms->node->pid, ms->state.exit_status);
#endif
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
