/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:05:37 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/22 20:08:28 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "errors.h"
#include "arena_list.h"
#include "libft_str.h"
#include "str_utils.h"
#include "line_utils.h"
#include "file_utils.h"

static inline int		set_in_file(t_minishell *ms, t_node *node, char *file);
static inline int		set_out_file(t_minishell *ms, t_node *node, t_redir *r);
static inline void	set_in_heredoc(t_minishell *ms, t_node *node, char *eof);
static inline bool	process_redir(t_minishell *ms, t_node *node, t_redir *r);

void	setup_io(t_minishell *ms, t_node *node)
{
	t_list	*redirs;
	t_redir	*r;

	while (node)
	{
		redirs = node->cmd.redirs;
		node->cmd.redir_in = STDIN_FILENO;
		node->cmd.redir_out = STDOUT_FILENO;
		while (redirs)
		{
			r = (t_redir *)redirs->content;
			if (!process_redir(ms, node, r))
				break ;
			redirs = redirs->next;
		}
		node = node->next;
	}
}

static inline bool	process_redir(t_minishell *ms, t_node *node, t_redir *r)
{
	if (!r->file)
	{
		warning(\
ms, str_join(ms, r->name, ": ambiguous redirect", VOLATILE));
		if (r->type == IN)
			node->cmd.redir_in = ERROR;
		if (r->type == OUT)
			node->cmd.redir_out = ERROR;
		return (false);
	}
	else
	{
		if (r->type == IN)
			if (set_in_file(ms, node, r->file) == ERROR)
				return (false);
		if (r->type == HEREDOC)
			set_in_heredoc(ms, node, r->file);
		if (r->type == OUT || r->type == OUT_APPEND)
			if (set_out_file(ms, node, r) == ERROR)
				return (false);
	}
	return (true);
}

static inline void	set_in_heredoc(t_minishell *ms, t_node *node, char *eof)
{
	char			*line;
	unsigned int	lines;
	bool			is_quoted;

	if (node->cmd.redir_in != STDIN_FILENO && node->cmd.redir_in != ERROR)
		close(node->cmd.redir_in);
	node->cmd.redir_in = \
try_open(ms, ms->heredoc_file, O_RDWR | O_CREAT | O_TRUNC, RW_______);
	is_quoted = (ft_strchr(eof, '\"') || ft_strchr(eof, '\''));
	eof = remove_quotes(ms, eof);
	lines = 0;
	while (true)
	{
		line = get_line(ms, PROMPT);
		if (!line || !ft_strcmp(line, eof))
			break ;
		if (!is_quoted)
			line = expand_str(ms, line, EXPAND_HEREDOC);
		try_write_endl(ms, node->cmd.redir_in, line);
		++lines;
	}
	if (!line && !g_signal)
		eof_warning(ms, eof, ms->lineno - lines);
	close(node->cmd.redir_in);
	node->cmd.redir_in = try_open(ms, ms->heredoc_file, O_RDWR, 0);
	unlink(ms->heredoc_file);
}

static inline int	set_in_file(t_minishell *ms, t_node *node, char *file)
{
	if (node->cmd.redir_in != STDIN_FILENO && node->cmd.redir_in != ERROR)
		close(node->cmd.redir_in);
	node->cmd.redir_in = try_open(ms, file, O_RDONLY, 0);
	return (node->cmd.redir_in);
}

static inline int	set_out_file(t_minishell *ms, t_node *node, t_redir *r)
{
	int	o_flag;

	o_flag = O_WRONLY | O_CREAT;
	if (r->type == OUT_APPEND)
		o_flag |= O_APPEND;
	if (r->type == OUT)
		o_flag |= O_TRUNC;
	if (node->cmd.redir_out != STDOUT_FILENO && node->cmd.redir_out != ERROR)
		close(node->cmd.redir_out);
	node->cmd.redir_out = try_open(ms, r->file, o_flag, RW_RW_RW_);
	return (node->cmd.redir_out);
}
