/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:15:08 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/06 08:37:46 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "errors.h"
#include "libft_str.h"
#include "arena_list.h"
#include "arena.h"

static inline bool	is_valid_syntax(t_token *t, t_token *prev);
static inline void	set_node(t_minishell *ms, t_list **args, t_node **head);
static inline void	set_args(t_minishell *ms, t_list *args, t_node *head);
static inline void	add_redir(\
t_minishell *ms, t_node *head, t_token **tokens);

bool	parse_tokens(t_minishell *ms, t_token **tokens)
{
	t_token		*t;
	t_list		*args;
	t_node		*head;
	t_token		*prev;

	head = ms->node;
	args = NULL;
	prev = NULL;
	t_token **tok = tokens;
int i = 0;
while (*tok) {
    printf("[%d] type=%d src=%s pos=%ld\n", i, (*tok)->type, (*tok)->src, (*tok)->pos);
    ++tok;
    ++i;
}
	while (*tokens)
	{
		t = *tokens;
		if (!is_valid_syntax(t, prev))
		{
			warning_syntax(ms, t->src);
			return (false);
		}
		if (t->type == PIPE)
			set_node(ms, &args, &head);
		if (t->type == WORD && t->pos > 0 && (*(tokens- 1))->type == REDIR)
			add_redir(ms, head, tokens);
		else if (t->type == WORD)
			lstadd_back(&args, lstnew(ms, t->src));
		prev = *tokens;
		++tokens;
	}
	set_args(ms, args, head);
	return (true);
}

static inline bool	is_valid_syntax(t_token *t, t_token *prev)
{
	if (prev)
	{
		if (t->type == REDIR && prev->type == REDIR)
			return (false);
		if (t->type == NEW_LINE && prev->type != WORD)
			return (false);
	}
	if (t->type == PIPE)
	{
		if (!prev || prev->type != WORD)
			return (false);
	}
	return (true);
}

static inline void	set_node(t_minishell *ms, t_list **args, t_node **head)
{
	set_args(ms, *args, *head);
	(*head)->next = alloc_pool(ms, sizeof(*(*head)->next));
	*head = (*head)->next;
	*args = NULL;
}

// static inline void	set_args(t_minishell *ms, t_list *args, t_node *head)
// {
// 	if (!args)
// 		return ;
// 	head->cmd.argc = lstsize(args);
// 	head->cmd.args = alloc_pool(ms, sizeof(*head->cmd.args) * (head->cmd.argc + 1));
// 	while (args)
// 	{
// 		*head->cmd.args++ = args->content;
// 		args = args->next;
// 	}
// 	head->cmd.args -= head->cmd.argc;
// }

static inline void set_args(t_minishell *ms, t_list *args, t_node *head)
{
    if (!args)
        return;
    head->cmd.argc = lstsize(args);
    head->cmd.args = alloc_pool(ms, sizeof(*head->cmd.args) * (head->cmd.argc + 1));

    t_list *tmp = args;
    for (int i = 0; i < head->cmd.argc; ++i)
    {
        head->cmd.args[i] = tmp->content;
        tmp = tmp->next;
    }
    head->cmd.args[head->cmd.argc] = NULL;
}

static inline void	add_redir(\
t_minishell *ms, t_node *head, t_token **tokens)
{
	t_redir	*redir;
	t_token	*t;
	t_token	*prev;

	t = *tokens;
	prev = *(tokens - 1);
	redir = alloc_pool(ms, sizeof(*redir));
	if (!ft_strcmp(prev->src, "<"))
		redir->type = IN;
	else if (!ft_strcmp(prev->src, ">"))
		redir->type = OUT;
	else if (!ft_strcmp(prev->src, ">>"))
		redir->type = OUT_APPEND;
	else if (!ft_strcmp(prev->src, "<<"))
		redir->type = HEREDOC;
	redir->filename = t->src;
	lstadd_back(&head->cmd.redirs, lstnew(ms, redir));
}
