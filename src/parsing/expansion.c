/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:07:18 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/07 20:22:54 by myli-pen         ###   ########.fr       */
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
static inline bool	expand(t_minishell *ms, char **str, char **result, char **quote, t_expand_mode mode);

void	expand_variables(t_minishell *ms)
{
	t_node	*node;

	node = ms->node;
	while(node)
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
		expand_str(ms, args, EXPAND_DEFAULT);
		split_words(ms, *args, &list);
		++args;
	}
	size = lstsize(list);
	args = alloc_volatile(ms, (size + 1) * sizeof(char *));
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
	char	*raw_file;

	redirs = raw_redirs;
	list = NULL;
	while (redirs)
	{
		r = (t_redir *)redirs->content;
		raw_file = r->file;
		if (r->type != HEREDOC)
		{
			expand_str(ms, &r->file, EXPAND_DEFAULT);
			split_words(ms, r->file, &list);
			if (list)
				r->file = remove_quotes(ms, list->content);
			if (!list || list->next)
				r->file = raw_file;
		}
		redirs = redirs->next;
	}
}
#include <stdio.h>
static inline bool	expand(t_minishell *ms, char **str, char **result, char **quote, t_expand_mode mode)
{
	char	*ptr;
	size_t	i;

	if (!**str || (*quote && **str == **quote))
		*result = str_join(ms, *result, "$", VOLATILE);
	else if (**str == '?')
	{
		*result = str_join(ms, *result, uint_to_str(ms, ms->state.exit_status), VOLATILE);
		(*str)++;
	}
	else
		join_var(ms, str, result, *quote, mode);
	ptr = ft_strchr(*str, '$');
	if (!ptr)
		return (false);
	if (*quote && *quote < ptr)
		*quote = NULL;
	if (!*quote)
	{
		*quote = find_quote(*str + 1);
		if (*quote && *quote > *str)
			*quote = NULL;
		i = 0;
		while (*quote && &((*quote)[i]) < *str)
		{
			++i;
			if (**quote == (*quote)[i])
			{
				*quote = find_quote(&((*quote)[i + 1]));
				i = 0;
			}
		}
	}
	if (*quote && *quote > *str)
		*quote = NULL;
	*result = str_join(ms, *result, str_sub(ms, VOLATILE, *str, ptr - *str), VOLATILE);
	*str = ptr;
	return (true);
}

bool	expand_str(t_minishell *ms, char **src, t_expand_mode mode)
{
	char	*str;
	char	*result;
	size_t	i;
	char	*quote;

	str = ft_strchr(*src, '$');
	if (!str)
		return (false);
	i = str - *src;
	result = alloc_volatile(ms, i + 1);
	ft_memcpy(result, *src, i);
	quote = find_quote(*src);
	i = 0;
	while (quote && &(quote[i]) < str)
	{
		++i;
		if (*quote == quote[i])
		{
			quote = find_quote(&(quote[i + 1]));
			i = 0;
		}
	}
	if (quote && quote > str)
		quote = NULL;
	while (str++)
	{
		if (!expand(ms, &str, &result, &quote, mode))
			break;
	}
	result = str_join(ms, result, str, VOLATILE);
	*src = result;
	return (true);
}

void	split_words(t_minishell *ms, char *src, t_list **list)
{
	size_t	i;
	size_t	k;
	size_t	quotes;
	char	*ifs;
	char	quote;
	char	*new;

	ifs = get_env_val(ms, "IFS");
	src = str_trim(src, ifs);
	quotes = 0;
	//printf("SRC: %s\n", src);
	while (*src)
	{
		i = 0;
		while (*src && (!is_whitespace(src, ifs) || quotes % 2 != 0))
		{
			if (*src == '\'' || *src == '\"')
			{
				quote = *src;
				++i;
				++src;
				++quotes;
				while (*src && *src != quote)
				{
					if (*src == '\'' || *src == '\"')
						++quotes;
					++i;
					++src;
				}
				quote = 0;
				++i;
				++src;
				++quotes;
			}
			else
			{
				++i;
				++src;
			}
		}
		new = alloc_volatile(ms, i + 1);
		k = 0;
		while (i)
		{
			new[k] = *(src - i);
			++k;
			--i;
		}
		lstadd_back(list, lstnew(ms, new));
		while (*src && is_whitespace(src, ifs))
			++src;
	}
}

char	*remove_quotes(t_minishell *ms, char *src)
{
	char	*result;
	char	*quote;
	size_t	i;
	size_t	k;
	bool	is_double;

	is_double = false;
	quote = find_quote(src);
	if (!quote)
		return (src);
	i = quote - src;
	result = alloc_volatile(ms, i + 1);
	ft_memcpy(result, src, i);
	while (*src)
	{
		i = 0;
		k = 1;
		if (*quote == '\"' && *(quote + 1) == '\'' && *(quote + 2) && *(quote + 2) == '\"')
		{
			k = 2;
			is_double = true;
		}
		src = quote + k;
		while (src[i] != *quote || is_double)
		{
			if (is_double)
				is_double = false;
			++i;
		}
		result = str_join(ms, result, str_sub(ms, VOLATILE, src, i), VOLATILE);
		src += i + k;
		if (!*(src + 1))
			break;
		quote = find_quote(src + (k == 2));
		if (!quote)
			break;
		result = str_join(ms, result, str_sub(ms, VOLATILE, src, quote - src), VOLATILE);
	}
	result = str_join(ms, result, src, VOLATILE);
	return (result);
}
