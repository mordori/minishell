/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:05:37 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/23 20:51:41 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "errors.h"
#include "arena_list.h"
#include "libft_str.h"
#include "str_utils.h"
#include "line_utils.h"

static inline int	set_in_file(t_minishell *ms, t_node *node, char *file);
static inline int	set_out_file(t_minishell *ms, t_node *node, t_redir *r);
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
			if (r->type == IN)
				if (set_in_file(ms, node, r->file) == ERROR)
					break ;
			if (r->type == HEREDOC)
				set_in_heredoc(ms, node, r->file);
			if (r->type == OUT || r->type == OUT_APPEND)
				if (set_out_file(ms, node, r) == ERROR)
					break ;
			redirs = redirs->next;
		}
		set_pipe(ms, node);
		node = node->next;
	}
}

static inline void	set_pipe(t_minishell *ms, t_node *node)
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
	static char		*file = "/tmp/heredoc.tmp";
	char			*line;
	unsigned int	lines;

	if (node->cmd.in > STDOUT_FILENO)
		close(node->cmd.in);
	node->cmd.in = try_open(ms, file, O_RDWR | O_CREAT | O_TRUNC, RW_______);
	if (!g_signal)
	{
		lines = 0;
		while (true)
		{
			line = get_line(ms, PROMPT);
			if (!line || !ft_strcmp(line, eof) || g_signal)
				break ;
			try_write_endl(ms, node->cmd.in, line);
			++lines;
		}
		if (!line)
			eof_warning(ms, eof, ms->lineno - lines);
	}
	close(node->cmd.in);
	node->cmd.in = try_open(ms, file, O_RDWR, 0);
	unlink(file);
}

static inline int	set_in_file(t_minishell *ms, t_node *node, char *file)
{
	if (node->cmd.in > STDOUT_FILENO)
		close(node->cmd.in);
	node->cmd.in = try_open(ms, file, O_RDONLY, 0);
	return (node->cmd.in);
}

static inline int	set_out_file(t_minishell *ms, t_node *node, t_redir *r)
{
	int	o_flag;

	o_flag = O_WRONLY | O_CREAT;
	if (r->type == OUT_APPEND)
		o_flag |= O_APPEND;
	if (r->type == OUT)
		o_flag |= O_TRUNC;
	if (node->cmd.out > STDOUT_FILENO)
		close(node->cmd.out);
	node->cmd.out = try_open(ms, r->file, o_flag, RW_RW_RW_);
	return (node->cmd.out);
}
