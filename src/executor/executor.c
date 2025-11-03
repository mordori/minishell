/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:09:55 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/03 17:46:41 by jvalkama         ###   ########.fr       */
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
		//update_env_lastcmd(ms, ms->node->cmd.cmd, ms->node->cmd.builtin);
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
	return (SUCCESS);
}

int	execute_pipeline(t_minishell *ms)
{
	int		prev_read;
	t_node	*node;

	node = ms->node;
	prev_read = -1;
	while (node)
	{
		if (command_verification(ms, node))
			return (ERROR_PIPELINE);
		//update_env_lastcmd(ms, node->cmd.cmd, node->cmd.builtin);
		if (node->cmd.out != ERROR && node->cmd.out != ERROR)
			ms->state.exit_status = spawn_and_run(ms, node, &prev_read);
		if (ms->state.exit_status)
			return (ERROR_PIPELINE);
		if (!node->next)
			break;
		node = node->next;
	}
	if (wait_pids(ms))
		warning(ms, NULL);
	return (SUCCESS);
}

int	wait_pids(t_minishell *ms)
{
	int		status;
	t_node	*node;

	node = ms->node;
	while (node)
	{
		waitpid(node->pid, &status, 0);
		if (WIFEXITED(status))
			ms->state.exit_status = WEXITSTATUS(status);
		if (ms->state.exit_status)
			return (ms->state.exit_status);
		node = node->next;
	}
	return (SUCCESS);
}
