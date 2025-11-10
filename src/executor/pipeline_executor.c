/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/07 15:25:18 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "io.h"

void	spawn_and_run(t_minishell *ms, t_node *node)
{
	pid_t		child_pid;
	int			status;
	t_node		*temp;

	child_pid = -1;
	status = command_verification(ms, node);
	if (node->next)
		set_pipe(ms, node);
	if (node->cmd.in != ERROR && node->cmd.out != ERROR && status == SUCCESS)
		try_fork(ms, &child_pid);
	if (child_pid != 0)
	{
		if (node->cmd.in != STDIN_FILENO)
			close(node->cmd.in);
		if (node->cmd.out != STDOUT_FILENO)
			close(node->cmd.out);
		node->pid = child_pid;
	}
	if (child_pid == 0)
	{
		temp = ms->node;
		while (temp)
		{
			if (temp->cmd.in != STDIN_FILENO && temp->cmd.in != node->cmd.in)
				close(temp->cmd.in);
			if (temp->cmd.out != STDOUT_FILENO && temp->cmd.out != node->cmd.out)
				close(temp->cmd.out);
			temp = temp->next;
		}
		if (!node->cmd.builtin)
			dup_io(node);
		run_node(ms, node);
	}
}

void	try_fork(t_minishell *ms, pid_t *child_pid)
{
	*child_pid = fork();
	if (*child_pid == -1)
		error_exit(ms, "");
}
