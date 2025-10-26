/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:07:18 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/27 01:37:36 by myli-pen         ###   ########.fr       */
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

static inline void	expand_str(t_minishell *ms, char **src);
static inline void	expand_args(t_minishell *ms, char **args);
static inline void	join_var_name(t_minishell *ms, char **str, char **result);
static inline void	join_var(t_minishell *ms, char **str, char **result, char c);
static inline void	expand_redirs(t_minishell *ms, t_list *redirs);

void	expand_variables(t_minishell *ms)
{
	t_node	*node;

	node = ms->node;
	while(node)
	{
		if (node->cmd.args)
			expand_args(ms, node->cmd.args);
		expand_redirs(ms, node->cmd.redirs);
		node = node->next;
	}
}

static inline void	expand_args(t_minishell *ms, char **raw_args)
{
	while (*raw_args)
	{
		expand_str(ms, raw_args);
		++raw_args;
	}
}

static inline void	expand_redirs(t_minishell *ms, t_list *raw_redirs)
{
	t_list	*redirs;
	t_redir	*r;

	redirs = raw_redirs;
	while (redirs)
	{
		r = (t_redir *)redirs->content;
		expand_str(ms, &r->file);
		redirs = redirs->next;
	}
}

static inline void	expand_str(t_minishell *ms, char **src)
{
	char	*str;
	char	*ptr;
	char	*result;
	size_t	i;
	char	quote;

	str = ft_strchr(*src, '$');
	if (!str)
		return ;
	i = str - *src;
	result = alloc_volatile(ms, i + 1);
	ft_memcpy(result, *src, i);
	quote = 0;
	if (i > 0 && ((*src)[i - 1] == '\'' || (*src)[i - 1] == '\"'))
		quote = (*src)[i - 1];
	while (str++)
	{
		if (!*str)
			result = str_join(ms, result, "$", VOLATILE);
		if (*str == '?')
			result = str_join(ms, result, uint_to_str(ms, ms->state.exit_status), VOLATILE);
		else if (*str == '$')
			result = str_join(ms, result, uint_to_str(ms, (unsigned int)getpid()), VOLATILE);
		else if (*str == '\"' || *str == '\'')
			join_var_name(ms, &str, &result);
		else
			join_var(ms, &str, &result, quote);
		++str;
		ptr = ft_strchr(str, '$');
		if (ptr)
			result = str_join(ms, result, str_sub(ms, VOLATILE, str, ptr - str), VOLATILE);
		else
			break ;
		if (!quote && ptr - str > 2 && (*(ptr - 1) == '\'' || *(ptr - 1) == '\"'))
			quote = *(ptr - 1);
		str = ptr;
	}
	result = str_join(ms, result, str, VOLATILE);
	*src = result;
}

static inline void	join_var_name(t_minishell *ms, char **str, char **result)
{
	size_t	i;
	char	c;
	char	*name;

	c = **str;
	i = 0;
	while ((*str)[i] != c)
		++i;
	name = str_sub(ms, VOLATILE, (*str), i + 1);
	*result = str_join(ms, *result, name, VOLATILE);
	*str += i;
}

static inline void	join_var(t_minishell *ms, char **str, char **result, char quote)
{
	size_t	i;
	char	*val;
	char	*name;

	i = 0;
	while ((*str)[i] && (*str)[i] != quote && (*str)[i] != '$')
		++i;
	if (!quote || quote == '\"')
	{
		name = str_sub(ms, VOLATILE, *str, i);
		val = get_env_val(ms, name);
	}
	if (quote == '\'')
	{
		(*str)--;
		++i;
		val = str_sub(ms, VOLATILE, *str, i);
	}
	if ((*str)[i] == quote)
		quote = 0;
	*result = str_join(ms, *result, val, VOLATILE);

	*str += i - 1;
}
