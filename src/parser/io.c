/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:05:37 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/17 23:27:31 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "errors.h"
#include "arena_list.h"
#include "libft_str.h"
#include "str_utils.h"
#include "line_utils.h"

static inline bool	set_in_file(t_minishell *ms, t_node *node, char *filename);
static inline bool	set_out_file(t_minishell *ms, t_node *node, t_redir *r);
static inline void	set_in_heredoc(t_minishell *ms, t_node *node, char *eof);
static inline void	set_pipe(t_minishell *ms, t_node *node);;

void	setup_io(t_minishell *ms, t_node *node)
{
	t_redir	*r;
	t_list	*redirs;

	while (node)
	{
		redirs = node->cmd.redirs;
		node->cmd.in = STDIN_FILENO;
		node->cmd.out = STDOUT_FILENO;
		while (redirs)
		{
			r = (t_redir *)redirs->content;
#ifdef DEBUG
if (r->type == UNDEFINED)
	printf("UNDEFINED TOKEN TYPE!");
#endif
			if (r->type == IN)
				if (!set_in_file(ms, node, r->filename))
					break ;
			if (r->type == HEREDOC)
				set_in_heredoc(ms, node, r->filename);
			if (r->type == OUT || r->type == OUT_APPEND)
				if (!set_out_file(ms, node, r))
					break ;
			redirs = redirs->next;
		}
		set_pipe(ms, node);
		node = node->next;
	}
}

void	set_pipe(t_minishell *ms, t_node *node)
{
	int	pipefd[2];

	if (node != ms->node)
	{
		if (pipe(pipefd) == ERROR)
			error_exit(ms, "pipe failed");
		if (node->cmd.in == STDIN_FILENO)
			node->cmd.in = pipefd[0];
		else
			close(pipefd[0]);
		if (node->cmd.out == STDOUT_FILENO)
			node->cmd.out = pipefd[1];
		else
			close(pipefd[1]);
	}
	node->pipe_fds[0] = node->cmd.in;
	node->pipe_fds[1] = node->cmd.out;
}

static inline void	set_in_heredoc(t_minishell *ms, t_node *node, char *eof)
{
	const char	*filename = "/tmp/heredoc.tmp";

	if (node->cmd.in > STDOUT_FILENO)
		close(node->cmd.in);
	node->cmd.in = open(filename, O_RDWR | O_CREAT | O_TRUNC, RW_______);
	if (node->cmd.in == ERROR)
		error_exit(ms, "heredoc create failed");
	if (!g_signal)
		write_heredoc(ms, node, eof);
	close(node->cmd.in);
	node->cmd.in = open(filename, O_RDWR);
	if (node->cmd.in == ERROR)
		error_exit(ms, "heredoc open failed");
	unlink(filename);
}

static inline bool	set_in_file(t_minishell *ms, t_node *node, char *filename)
{
	if (node->cmd.in > STDOUT_FILENO)
		close(node->cmd.in);
	node->cmd.in = open(filename, O_RDONLY);
	if (node->cmd.in == ERROR)
	{
		warning(ms, filename);
		return (false);
	}
	return (true);
}

static inline bool	set_out_file(t_minishell *ms, t_node *node, t_redir *r)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (r->type == OUT_APPEND)
		flags |= O_APPEND;
	if (r->type == OUT)
		flags |= O_TRUNC;
	if (node->cmd.out > STDOUT_FILENO)
		close(node->cmd.out);
	node->cmd.out = open(r->filename, flags, RW_RW_RW_);
	if (node->cmd.out == ERROR)
	{
		warning(ms, r->filename);
		return (false);
	}
	return (true);
}
