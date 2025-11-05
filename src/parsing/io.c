/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:05:37 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/04 18:46:02 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "errors.h"
#include "arena_list.h"
#include "libft_str.h"
#include "str_utils.h"
#include "line_utils.h"
#include "parsing.h"

static inline int	set_in_file(t_minishell *ms, t_node *node, char *file);
static inline int	set_out_file(t_minishell *ms, t_node *node, t_redir *r);
static inline void	set_in_heredoc(t_minishell *ms, t_node *node, char *eof);

bool	setup_io(t_minishell *ms, t_node *node)
{
	t_redir	*r;
	t_list	*redirs;
	bool	status;

	status = true;
	while (node)
	{
		redirs = node->cmd.redirs;
		node->cmd.in = STDIN_FILENO;
		node->cmd.out = STDOUT_FILENO;
		while (redirs)
		{
			r = (t_redir *)redirs->content;
			if (*r->file == '$' && *(r->file + 1) && (*(r->file + 1) != '$' || *(r->file + 1) != '?'))
			{
				status = false;
				warning(ms, str_join(ms, r->file, ": ambiguous redirect", VOLATILE));
			}
			else
			{
				if (r->type == IN)
					if (set_in_file(ms, node, r->file) == ERROR)
						break ;
				if (r->type == HEREDOC)
					set_in_heredoc(ms, node, r->file);
				if (r->type == OUT || r->type == OUT_APPEND)
					if (set_out_file(ms, node, r) == ERROR)
						break ;
			}
			redirs = redirs->next;
		}
		node = node->next;
	}
	return (status);
}

void	set_pipe(t_minishell *ms, t_node *node)
{
	int	pipefd[2];

	if (node->next)
	{
		if (pipe(pipefd) == ERROR)
			error_exit(ms, "pipe failed");
		if (node->next->cmd.in == STDIN_FILENO)
			node->next->cmd.in = pipefd[0];
		else
			close(pipefd[0]);
		if (node->cmd.out == STDOUT_FILENO)
			node->cmd.out = pipefd[1];
		else
			close(pipefd[1]);
	}
}

static inline void	set_in_heredoc(t_minishell *ms, t_node *node, char *eof)
{
	static char		*file = "/tmp/heredoc.tmp";
	char			*line;
	unsigned int	lines;
	bool			is_quoted;

	if (node->cmd.in > STDOUT_FILENO)
		close(node->cmd.in);
	node->cmd.in = try_open(ms, file, O_RDWR | O_CREAT | O_TRUNC, RW_______);
	is_quoted = ft_strchr(eof, '\"') || ft_strchr(eof, '\'');
	eof = remove_quotes(ms, eof);
	if (!g_signal)
	{
		lines = 0;
		while (true)
		{
			line = get_line(ms, PROMPT);
			if (!line || !ft_strcmp(line, eof) || g_signal)
				break ;
			if (!is_quoted)
				expand_str(ms, &line, EXPAND_HEREDOC);
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
