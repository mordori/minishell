/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/05 17:51:21 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "io.h"

void	spawn_and_run(t_minishell *ms, t_node *node)
{
	pid_t		child_pid;

	child_pid = -1;
	if (node->next)
		set_pipe(ms, node);
	if (node->cmd.in != ERROR && node->cmd.out != ERROR)
		try_fork(ms, &child_pid);
	if (child_pid != 0)
	{
		if (node->next)
		{
			if (close(node->cmd.out))
				error_exit(ms, "");
		}
	}
	if (child_pid != 0)
		node->pid = child_pid;
	if (child_pid == 0)
	{
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
