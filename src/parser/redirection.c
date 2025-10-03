/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:05:37 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/03 18:06:15 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "errors.h"
#include "arena_list.h"
#include "libft_str.h"

static inline bool	set_in(t_minishell *ms, t_node *node, char *filename);
static inline void	set_out(t_minishell *ms, t_node *node, t_redir *r);
static inline void	set_heredoc(t_minishell *ms, t_node *node, char *eof);

void	redirect_io(t_minishell *ms)
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
				if (!set_in(ms, node, r->filename))
					break ;
			if (r->type == HEREDOC)
				set_heredoc(ms, node, r->filename);
			if (r->type == OUT || r->type == OUT_APPEND)
				set_out(ms, node, r);
			head = head->next;
		}
		node = node->next;
	}
}

// Need to set fd
static inline void	set_heredoc(t_minishell *ms, t_node *node, char *eof)
{
	int		fd;
	char	*line;

	(void)ms;
	fd = 322;
	line = readline("> ");
	while (ft_strcmp(line, eof))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	node->cmd.in = fd;
}

static inline bool	set_in(t_minishell *ms, t_node *node, char *filename)
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

static inline void	set_out(t_minishell *ms, t_node *node, t_redir *r)
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
		error_exit(ms, "opening file failed");
}
