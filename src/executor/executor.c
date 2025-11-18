/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:09:55 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/18 19:05:39 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "cleanup.h"

static void	wait_pids(t_minishell *ms);

void	executor(t_minishell *ms)
{
	if (!ms->node->cmd.args)
	{
		close_all_fds(ms);
		return ;
	}
	set_mode(ms);
	if (ms->state.mode == SIMPLE)
	{
		if (ms->node->cmd.redir_in == ERROR || ms->node->cmd.redir_out == ERROR)
		{
			ms->state.exit_status = ERROR_GENERAL;
			close_all_fds(ms);
			return ;
		}
		ms->state.exit_status = execute_simple(ms);
		update_env_lastcmd(ms, ms->node->cmd.cmd, ms->node->cmd.builtin);
	}
	else if (ms->state.mode == PIPELINE)
	{
		ms->state.exit_status = execute_pipeline(ms);
	}
	close_all_fds(ms);
}

int	execute_simple(t_minishell *ms)
{
	pid_t	child_pid;
	int		status;

	status = command_verification(ms, ms->node);
	if (status)
		return (status);
	if (ms->node->cmd.builtin \
&& ms->node->cmd.redir_in == STDIN_FILENO \
&& ms->node->cmd.redir_out == STDOUT_FILENO)
		return (exec_builtin(ms, ms->node));
	try_fork(ms, &child_pid);
	if (child_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_DFL);
		dup_redirections(ms, ms->node);
		run_node(ms, ms->node);
	}
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		ms->state.exit_status = WEXITSTATUS(status);
	return (ms->state.exit_status);
}

int	execute_pipeline(t_minishell *ms)
{
	t_node	*node;
	int		pipefd[2];
	int		in;

	node = ms->node;
	in = STDIN_FILENO;
	while (node)
	{
		if (node->next)
			if (pipe(pipefd) == ERROR)
				error_exit(ms, "pipe failed");
		if (node->cmd.args)
			spawn_and_run(ms, node, in, pipefd);
		if (in != STDIN_FILENO)
			close(in);
		close_node_fds(node);
		if (node->next)
		{
			close(pipefd[1]);
			in = pipefd[0];
		}
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
		if (node->pid > 0)
		{
			waitpid(node->pid, &status, 0);
			if (WIFEXITED(status))
				ms->state.exit_status = WEXITSTATUS(status);
		}
		if (node->cmd.redir_in == ERROR || node->cmd.redir_out == ERROR)
			ms->state.exit_status = ERROR_GENERAL;
		node = node->next;
	}
}
