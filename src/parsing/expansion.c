/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:07:18 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/04 22:39:07 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "str_utils.h"
#include "arena_list.h"
#include "arena.h"
#include "env.h"

#ifdef DEBUG
#include <stdio.h>
#endif

static inline void	expand_args(t_minishell *ms, t_node *node, char **args);
static inline void	expand_redirs(t_minishell *ms, t_list *redirs);
static inline bool	expand(t_minishell *ms, char **str, char **result, char *quote, t_expand_mode mode);

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
	//bool	is_expanded;
	t_list	*list;
	size_t	size;

	list = NULL;
	args = raw_args;
	while (*args)
	{
		expand_str(ms, args, EXPAND_DEFAULT);
		remove_quotes(ms, *args, &list);
		++args;
	}
	size = lstsize(list);
	args = alloc_volatile(ms, (size + 1) * sizeof(char *));
	while (list)
	{
		*args = list->content;
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
	//bool	is_expanded;

	redirs = raw_redirs;
	while (redirs)
	{
		r = (t_redir *)redirs->content;
		if (r->type != HEREDOC)
		{
			expand_str(ms, &r->file, EXPAND_DEFAULT);
			// r->file = remove_quotes(ms, r->file);
		}
		redirs = redirs->next;
	}
}

static inline bool	expand(t_minishell *ms, char **str, char **result, char *quote, t_expand_mode mode)
{
	char	*ptr;

	if (!**str || (*quote && **str == *quote))
		*result = str_join(ms, *result, "$", VOLATILE);
	else if (**str == '?')
		*result = str_join(ms, *result, uint_to_str(ms, ms->state.exit_status), VOLATILE);
	else if (**str == '$')
		*result = str_join(ms, *result, uint_to_str(ms, (unsigned int)getpid()), VOLATILE);
	else if (**str == '\"' || **str == '\'')
		join_var_name(ms, str, result, mode);
	else
		join_var(ms, str, result, *quote, mode);
	if (**str && !(*quote && **str == *quote))
		++(*str);
	ptr = ft_strchr(*str, '$');
	if (!ptr)
		return (false);
	*result = str_join(ms, *result, str_sub(ms, VOLATILE, *str, ptr - *str), VOLATILE);
	if (!*quote && ptr - *str > 2 && (*(ptr - 1) == '\'' || *(ptr - 1) == '\"'))
		*quote = *(ptr - 1);
	*str = ptr;
	return (true);
}

bool	expand_str(t_minishell *ms, char **src, t_expand_mode mode)
{
	char	*str;
	char	*result;
	size_t	i;
	char	quote;

	str = ft_strchr(*src, '$');
	if (!str)
		return (false);
	i = str - *src;
	result = alloc_volatile(ms, i + 1);
	ft_memcpy(result, *src, i);
	quote = 0;
	if (i > 0 && ((*src)[i - 1] == '\'' || (*src)[i - 1] == '\"'))
		quote = (*src)[i - 1];
	while (str++)
	{
		if (!expand(ms, &str, &result, &quote, mode))
			break;
	}
	result = str_join(ms, result, str, VOLATILE);
	*src = result;
	return (true);
}

char	*remove_quotes(t_minishell *ms, char *src, t_list **list)
{
	char	*result;
	char	*ptr;
	size_t	i;
	size_t	k;
	char	*ifs;
	char	quote;
	char	*new;

	ifs = get_env_val(ms, "IFS");
	src = str_trim(src, ifs);
	while (*src)
	{
		i = 0;
		while (*src && !is_whitespace(src, ifs))
		{
			if (*src == '\'' || *src == '\"')
			{
				quote = *src++;
				++i;
				while (*src && *src != quote)
				{
					++i;
					++src;
				}
				quote = 0;
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
			if (*(src - i) && (*(src - i) == '\'' || *(src - i) == '\"'))
			{
				--i;
				continue ;
			}
			new[k] = *(src - i);
			++k;
			--i;
		}
		lstadd_back(list, lstnew(ms, new));
		while (*src && is_whitespace(src, ifs))
			++src;
	}


	ptr = find_quote(src);
	if (!ptr)
		return (src);
	result = alloc_volatile(ms, ptr - src + 1);
	ft_memcpy(result, src, ptr - src);
	src = ptr + 1;
	while (*src)
	{
		i = 0;
		while (src[i] != *ptr)
			++i;
		result = str_join(ms, result, str_sub(ms, VOLATILE, src, i), VOLATILE);
		src += i + 1;
		ptr = find_quote(src);
		if (!ptr)
			break;
		result = str_join(ms, result, str_sub(ms, VOLATILE, src, ptr - src), VOLATILE);
		src = ptr;
	}
	result = str_join(ms, result, src, VOLATILE);
	return (result);
}
