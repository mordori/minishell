/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:09:55 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/07 11:38:39 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	wait_pids(t_minishell *ms);

void	executor(t_minishell *ms)
{
	set_mode(ms);
	if (ms->state.mode == SIMPLE)
	{
		ms->state.exit_status = execute_simple(ms);
	}
	else if (ms->state.mode == PIPELINE)
	{
		ms->state.exit_status = execute_pipeline(ms);
	}
}

int	execute_simple(t_minishell *ms)
{
	pid_t	child_pid;
	int		status;

	status = command_verification(ms, ms->node);
	if (status)
		return (status);
	update_env_lastcmd(ms, ms->node->cmd.cmd, ms->node->cmd.builtin);
	if (ms->node->cmd.out == ERROR || ms->node->cmd.out == ERROR)
		return (ERROR);
	if (ms->node->cmd.builtin)
		return (exec_builtin(ms, ms->node));
	else
	{
		try_fork(ms, &child_pid);
		if (child_pid == 0)
		{
			dup_io(ms->node);
			if (exec_extern(ms, ms->node))
				error_exit(ms, NULL);
		}
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			ms->state.exit_status = WEXITSTATUS(status);
	}
	return (ms->state.exit_status);
}

int	execute_pipeline(t_minishell *ms)
{
	t_node	*node;

	node = ms->node;
	while (node)
	{
		if (command_verification(ms, node))
			return (ERROR_PIPELINE);
		update_env_lastcmd(ms, node->cmd.cmd, node->cmd.builtin);
		spawn_and_run(ms, node);
		node = node->next;
	}
	wait_pids(ms);
	return (ms->state.exit_status);
}

static void	wait_pids(t_minishell *ms)
{
	int		status;
	t_node	*node;

	node = ms->node;
	while (node)
	{
		if (node->pid)
			waitpid(node->pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (ms->state.exit_status == 0)
			{
				ms->state.exit_status = WEXITSTATUS(status);
				if (ms->state.exit_status != 0)
					warning(ms, NULL);
			}
		}
		node = node->next;
	}
}
