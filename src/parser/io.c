/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:05:37 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/15 20:28:18 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "errors.h"
#include "arena_list.h"
#include "libft_str.h"
#include "str_utils.h"
#include "main.h"

static inline bool	set_in_file(t_minishell *ms, t_node *node, char *filename);
static inline bool	set_out_file(t_minishell *ms, t_node *node, t_redir *r);
static inline void	set_in_heredoc(t_minishell *ms, t_node *node, char *eof);

void	setup_io(t_minishell *ms)
{
	t_redir	*r;
	t_node	*node;
	t_list	*head;

	node = ms->node;
	while (node)
	{
		head = node->cmd.redirs;
		node->cmd.in = STDIN_FILENO;
		node->cmd.out = STDOUT_FILENO;
		while (head)
		{
			r = (t_redir *)head->content;
			if (r->type == IN)
				if (!set_in_file(ms, node, r->filename))
					break ;
			if (r->type == HEREDOC)
				set_in_heredoc(ms, node, r->filename);
			if (r->type == OUT || r->type == OUT_APPEND)
				if (!set_out_file(ms, node, r))
					break ;
			head = head->next;
		}
		node = node->next;
	}
}

void	dup_io(t_node *node)
{
	if (node->cmd.in != STDIN_FILENO)
	{
		dup2(node->cmd.in, STDIN_FILENO);
		close (node->cmd.in);
	}
	if (node->cmd.out != STDOUT_FILENO)
	{
		dup2(node->cmd.out, STDOUT_FILENO);
		close (node->cmd.out);
	}
}

static inline void	write_heredoc(t_minishell *ms, t_node *node, char *eof)
{
	char	*line;
	int		bytes;
	char	*w;
	int		i;

	bytes = 0;
	i = 0;
	line = readline(PROMPT);
	while (line && ft_strcmp(line, eof) && !g_signal)
	{
		bytes = write(node->cmd.in, line, ft_strlen(line));
		if (bytes != ERROR)
			bytes = write(node->cmd.in, "\n", 1);
		if (bytes == ERROR)
			break ;
		free(line);
		line = readline(PROMPT);
		++i;
	}
	if (line)
		free(line);
	else
	{
		w = str_join(ms, "warning: here-document at line ", int_to_str(ms, ms->lineno));
		w = str_join(ms, w, " delimited by end-of-file (wanted `");
		w = str_join(ms, w, eof);
		w = str_join(ms, w, "')");
		warning(ms, w);
	}
	ms->lineno += i;
	if (bytes == ERROR)
		error_exit(ms, "readline/write failed");
}

static inline int	rl_hook(void)
{
	if (g_signal == SIGINT)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}

void	sig_handler2(int sig)
{
	write(1, "^C", 2);
	g_signal = sig;
}

static inline void	set_in_heredoc(t_minishell *ms, t_node *node, char *eof)
{
	const char	*filename = "/tmp/heredoc.tmp";

	if (node->cmd.in > STDOUT_FILENO)
		close(node->cmd.in);
	node->cmd.in = open(filename, O_RDWR | O_CREAT | O_TRUNC, RW_______);
	if (node->cmd.in == ERROR)
		error_exit(ms, "heredoc create failed");
	ms->sa.sa_handler = sig_handler2;
	if (sigaction(SIGINT, &ms->sa, NULL) == ERROR)
		error_exit(ms, "sigaction init failed");
	rl_event_hook = rl_hook;
	write_heredoc(ms, node, eof);
	rl_event_hook = NULL;
	ms->sa.sa_handler = sig_handler;
	if (sigaction(SIGINT, &ms->sa, NULL) == ERROR)
		error_exit(ms, "sigaction init failed");
	close(node->cmd.in);
	node->cmd.in = open(filename, O_RDWR, RW_______);
	if (node->cmd.in == ERROR)
		error_exit(ms, "heredoc open failed");
	unlink(filename);
}

static inline bool	set_in_file(t_minishell *ms, t_node *node, char *filename)
{
	if (node->cmd.in > STDOUT_FILENO)
		close(node->cmd.in);
	node->cmd.in = open(filename, O_RDONLY, 0);
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
	if (r->type == OUT && !node->cmd.args)
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
