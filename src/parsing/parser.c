/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:15:08 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/17 20:55:43 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "errors.h"
#include "libft_str.h"
#include "arena_list.h"
#include "arena.h"

static inline bool	is_valid_syntax(t_token *t, t_token *prev);
static inline void	set_node(t_minishell *ms, t_list **args, t_node **node);
static inline void	set_args(t_minishell *ms, t_list *args, t_node *node);
static inline void	add_redir(\
t_minishell *ms, t_node *node, t_token **tokens);

bool	parse_tokens(t_minishell *ms, t_token **tokens)
{
	t_list		*args;
	t_node		*node;
	t_token		*prev;

	node = ms->node;
	args = NULL;
	prev = NULL;
	while (*tokens)
	{
		if (!is_valid_syntax(*tokens, prev))
		{
			warning_syntax(ms, (*tokens)->src);
			return (false);
		}
		if ((*tokens)->type == PIPE)
			set_node(ms, &args, &node);
		if (\
(*tokens)->type == WORD && (*tokens)->pos > 0 && prev->type == REDIR)
			add_redir(ms, node, tokens);
		else if ((*tokens)->type == WORD)
			lstadd_back(&args, lstnew(ms, (*tokens)->src));
		prev = *tokens;
		++tokens;
	}
	set_args(ms, args, node);
	return (true);
}

static inline bool	is_valid_syntax(t_token *t, t_token *prev)
{
	if (prev)
	{
		if (t->type == REDIR && prev->type == REDIR)
			return (false);
		if (t->type == NEW_LINE && (prev->type == REDIR || prev->type == PIPE))
			return (false);
	}
	if (t->type == PIPE)
	{
		if (!prev || prev->type != WORD)
			return (false);
	}
	return (true);
}

static inline void	set_node(t_minishell *ms, t_list **args, t_node **node)
{
	set_args(ms, *args, *node);
	(*node)->next = alloc_volatile(ms, sizeof(t_node));
	*node = (*node)->next;
	*args = NULL;
}

static inline void	set_args(t_minishell *ms, t_list *args, t_node *node)
{
	t_list	*temp;
	int		i;

	if (!args)
		return ;
	node->cmd.argc = (int)lstsize(args);
	node->cmd.args = alloc_volatile(ms, sizeof(char *) * (node->cmd.argc + 1));
	temp = args;
	i = 0;
	while (i < node->cmd.argc)
	{
		node->cmd.args[i] = temp->content;
		temp = temp->next;
		++i;
	}
	node->cmd.args[node->cmd.argc] = NULL;
}

static inline void	add_redir(\
t_minishell *ms, t_node *node, t_token **tokens)
{
	static size_t	heredocs = 0;
	t_redir			*redir;
	t_token			*t;
	t_token			*prev;

	t = *tokens;
	prev = *(tokens - 1);
	redir = alloc_volatile(ms, sizeof(t_redir));
	if (!ft_strcmp(prev->src, "<"))
		redir->type = IN;
	else if (!ft_strcmp(prev->src, ">"))
		redir->type = OUT;
	else if (!ft_strcmp(prev->src, ">>"))
		redir->type = OUT_APPEND;
	else if (!ft_strcmp(prev->src, "<<"))
	{
		redir->type = HEREDOC;
		++heredocs;
	}
	if (heredocs > MAX_HEREDOC)
		error_exit(ms, "maximum here-document count exceeded");
	redir->file = t->src;
	lstadd_back(&node->cmd.redirs, lstnew(ms, redir));
}
