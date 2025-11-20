/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:07:18 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/20 02:12:58 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "str_utils.h"
#include "arena_list.h"
#include "arena.h"
#include "env.h"

static inline void	expand_args(t_minishell *ms, t_node *node, char **args);
static inline void	expand_redirs(t_minishell *ms, t_list *redirs);

void	expand_variables(t_minishell *ms)
{
	t_node	*node;

	node = ms->node;
	while (node)
	{
		if (node->cmd.args)
			expand_args(ms, node, node->cmd.args);
		expand_redirs(ms, node->cmd.redirs);
		node = node->next;
	}
}

static inline void	expand_args(t_minishell *ms, t_node *node, char **raw_args)
{
	char	**args;
	t_list	*list;
	size_t	size;

	list = NULL;
	args = raw_args;
	while (*args)
	{
		*args = expand_str(ms, *args, EXPAND_DEFAULT);
		split_words(ms, *args, &list);
		++args;
	}
	size = lstsize(list);
	args = alloc_volatile(ms, (size + 1) * sizeof(char *));
	if (!list)
		args = NULL;
	while (list)
	{
		*args = remove_quotes(ms, list->content);
		unmask_quotes(*args);
		++args;
		list = list->next;
	}
	args -= size;
	node->cmd.args = args;
}

static inline void	expand_redirs(t_minishell *ms, t_list *raw_redirs)
{
	t_list	*redirs;
	t_redir	*r;
	t_list	*list;

	redirs = raw_redirs;
	list = NULL;
	while (redirs)
	{
		r = (t_redir *)redirs->content;
		r->name = r->file;
		if (r->type != HEREDOC)
		{
			r->file = expand_str(ms, r->file, EXPAND_DEFAULT);
			split_words(ms, r->file, &list);
			if (list)
				r->file = remove_quotes(ms, list->content);
			if (!list || list->next)
				r->file = NULL;
			list = list->next;
		}
		redirs = redirs->next;
	}
}

char	*expand_str(t_minishell *ms, char *src, t_expand_mode mode)
{
	t_ctx_exp	ctx;

	if (!ft_strchr(src, '$'))
		return (src);
	ft_memset(&ctx, 0, sizeof(ctx));
	ctx.result = alloc_volatile(ms, 1);
	while (*src)
	{
		if (*src == '$')
		{
			if(!expand(ms, &src, &ctx, mode))
				continue;
		}
		else
		{
			if (\
!ctx.quote && (*src == SQUOTE || *src == DQUOTE) && mode != EXPAND_HEREDOC)
				ctx.quote = *src;
			else if (\
*src == ctx.quote && mode != EXPAND_HEREDOC)
				ctx.quote = 0;
			append_chr(ms, &src, &ctx);
		}
	}
	ctx.result = str_join(ms, ctx.result, ctx.buf, VOLATILE);
	return (ctx.result);
}
