/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:05:37 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/03 05:01:28 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "errors.h"
#include "arena_list.h"

static inline bool	set_in(t_minishell *ms, t_node *node, char *filename);
static inline void	set_out(t_minishell *ms, t_node *node, t_redir *r);

void	redirect_io(t_minishell *ms)
{
	t_redir	*r;
	t_node	*node;
	t_list	*head;

	node = ms->node;
	while (node)
	{
		head = node->cmd.redirs;
		node->cmd.out = 0;
		node->cmd.in = 1;
		while (head)
		{
			r = (t_redir *)head->content;
			if (r->type == IN)
				if (!set_in(ms, node, r->filename))
					break ;
			if (r->type == OUT || r->type == OUT_APPEND)
				set_out(ms, node, r);
			head = head->next;
		}
		if (node->cmd.out == 0)
			node->cmd.out = STDOUT_FILENO;
		if (node->cmd.in == 1)
			node->cmd.in = STDIN_FILENO;
		node = node->next;
	}
}

static inline bool	set_in(t_minishell *ms, t_node *node, char *filename)
{
	int	flags;

	flags = O_RDONLY;
	if (node->cmd.in != 1)
		close(node->cmd.in);
	node->cmd.in = open(filename, flags, RWRWRW);
	if (node->cmd.in == ERROR)
	{
		if (node->cmd.out != 0)
			close(node->cmd.out);
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
	if (node->cmd.out != 0)
		close(node->cmd.out);
	node->cmd.out = open(r->filename, flags, RWRWRW);
	if (node->cmd.out == ERROR)
	{
		if (node->cmd.in != 1)
			close(node->cmd.in);
		error_exit(ms, "opening file failed");
	}
}
