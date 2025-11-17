/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/14 13:14:10 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "io.h"

static void	set_io(t_minishell *ms, t_node *node, int in, int pipefd[2]);

void	spawn_and_run(t_minishell *ms, t_node *node, int in, int pipefd[2])
{
	pid_t	child_pid;
	int		status;

	child_pid = -1;
	status = command_verification(ms, node);
	if (status == SUCCESS)
		try_fork(ms, &child_pid);
	node->pid = child_pid;
	if (child_pid == 0)
	{
		set_io(ms, node, in, pipefd);
		run_node(ms, node);
	}
	update_env_lastcmd(ms, node->cmd.cmd, node->cmd.builtin);
}

void	try_fork(t_minishell *ms, pid_t *child_pid)
{
	*child_pid = fork();
	if (*child_pid == -1)
		error_exit(ms, "fork failed");
}

static void	set_io(t_minishell *ms, t_node *node, int in, int pipefd[2])
{
	if (in != STDIN_FILENO)
	{
		if (dup2(in, STDIN_FILENO) == ERROR)
			error_exit(ms, "dup2 in failed");
		close(in);
	}
	if (node->next)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == ERROR)
			error_exit(ms, "dup2 out failed");
		close(pipefd[1]);
	}
	dup_redirections(ms, node);
	if (node->cmd.redir_in == ERROR || node->cmd.redir_out == ERROR)
	{
		clean(ms);
		exit(EXIT_FAILURE);
	}
}
