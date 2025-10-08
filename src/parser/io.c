/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:05:37 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/08 00:45:01 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "errors.h"
#include "arena_list.h"
#include "libft_str.h"

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

static inline void	set_in_heredoc(t_minishell *ms, t_node *node, char *eof)
{
	int		pipefd[2];
	char	*line;
	int		bytes;

	if (pipe(pipefd) == ERROR)
		error_exit(ms, "pipe creation failed");
	line = readline(PROMPT);
	while (line && ft_strcmp(line, eof))
	{
		bytes = write(pipefd[1], line, ft_strlen(line));
		if (bytes != ERROR)
			bytes = write(pipefd[1], "\n", 1);
		if (bytes == ERROR)
			break ;
		free(line);
		line = readline(PROMPT);
	}
	if (line)
		free(line);
	close(pipefd[1]);
	node->cmd.in = pipefd[0];
	if (!line || bytes == ERROR)
		error_exit(ms, "readline/write failed");
}

static inline bool	set_in_file(t_minishell *ms, t_node *node, char *filename)
{
	int	flags;

	flags = O_RDONLY;
	if (node->cmd.in > STDOUT_FILENO)
		close(node->cmd.in);
	node->cmd.in = open(filename, flags, 0);
	if (node->cmd.in == ERROR)
	{
		warning_file(ms, filename);
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
	node->cmd.out = open(r->filename, flags, RWRWRW);
	if (node->cmd.out == ERROR)
	{
		warning_file(ms, r->filename);
		return (false);
	}
	return (true);
}
