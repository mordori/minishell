/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:07:18 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/18 18:55:00 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "str_utils.h"
#include "arena_list.h"
#include "arena.h"
#include "env.h"


#include <stdio.h>


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
		// printf("ARGS: %s\n", *args);
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

bool	init_expand(t_minishell *ms, char **str, char **src, char **result)
{
	*str = ft_strchr(*src, '$');
	if (!*str)
		return (false);
	*result = alloc_volatile(ms, *str - *src + 1);
	ft_memcpy(*result, *src, *str - *src);
	return (true);
}

char	*expand_str(t_minishell *ms, char *src, t_expand_mode mode)
{
	char	*str;
	char	*result;
	char	*quote;

	if (!init_expand(ms, &str, &src, &result))
		return (src);
	quote = NULL;
	find_quote(src, &quote, str);
	while (str++)
	{
		if (!*str || is_whitespace(str, "") || (quote && *str == *quote) || \
*str == '$')
			result = str_join(ms, result, "$", VOLATILE);
		else if (*str == '?' && !(quote && *quote == '\'') && str++)
			result = str_join(\
ms, result, uint_to_str(ms, ms->state.exit_status), VOLATILE);
		else
			result = \
str_join(ms, result, join_var(ms, &str, quote, mode), VOLATILE);
		src = ft_strchr(str, '$');
		if (!src)
			break ;
		find_quote(str, &quote, src);
		result = str_join(\
ms, result, str_sub(ms, VOLATILE, str, src - str), VOLATILE);
		str = src;
	}
	return (str_join(ms, result, str, VOLATILE));
}
