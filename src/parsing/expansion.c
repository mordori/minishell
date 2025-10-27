/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:07:18 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/27 20:18:47 by myli-pen         ###   ########.fr       */
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

static inline void	expand_args(t_minishell *ms, char **args);
static inline void	join_var_name(t_minishell *ms, char **str, char **result, t_expand_mode mode);
static inline void	join_var(t_minishell *ms, char **str, char **result, char quote, t_expand_mode mode);
static inline void	expand_redirs(t_minishell *ms, t_list *redirs);
static inline char	*remove_quotes(t_minishell *ms, char *str);

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
	char	**args;

	args = raw_args;
	while (*args)
	{
		expand_str(ms, args, EXPAND_DEFAULT);
		remove_quotes(ms, args);
		++args;
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
		if (r->type != HEREDOC)
			expand_str(ms, &r->file, EXPAND_DEFAULT);
		redirs = redirs->next;
	}
}

void	expand_str(t_minishell *ms, char **src, t_expand_mode mode)
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
			join_var_name(ms, &str, &result, mode);
		else
			join_var(ms, &str, &result, quote, mode);
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

static inline void	join_var_name(t_minishell *ms, char **str, char **result, t_expand_mode mode)
{
	size_t	i;
	char	c;
	char	*name;

	c = **str;
	i = 0;
	while ((*str)[i] != c)
		++i;
	name = str_sub(ms, VOLATILE, (*str), i + 1);
	if (mode == EXPAND_HEREDOC)
		*result = str_join(ms, *result, "$", VOLATILE);
	*result = str_join(ms, *result, name, VOLATILE);
	*str += i;
}

static inline void	join_var(t_minishell *ms, char **str, char **result, char quote, t_expand_mode mode)
{
	size_t	i;
	char	*val;
	char	*name;

	i = 0;
	while ((*str)[i] && (*str)[i] != quote && (*str)[i] != '$')
		++i;
	if (!quote || quote == '\"' || mode == EXPAND_HEREDOC)
	{
		name = str_sub(ms, VOLATILE, *str, i);
		val = get_env_val(ms, name);
	}
	else if (quote == '\'')
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

char	*find_quote(char *str)
{
	char	*single_q;
	char	*double_q;

	single_q = ft_strchr(str, '\'');
	double_q = ft_strchr(str, '\"');
	if (!single_q && !double_q)
		return (NULL);
	if (single_q && single_q < double_q)
		return (single_q);
	else
		return (double_q);
}

static inline void	remove_quotes(t_minishell *ms, char **src)
{
	char	*result;
	char	*ptr;
	char	*str;
	char	q;
	size_t	i;

	ptr = find_quote(str);
	if (!ptr)
		return (str);
	result = alloc_volatile(ms, ptr - str + 1);
	ft_memcpy(result, str, ptr - str);
	q = *ptr;
	while (*str)
	{
		i = 0;
		while (str[i] != q)
			++i;
		result = str_join(ms, result, str_sub(ms, VOLATILE, str, i), VOLATILE);
		str += i + 1;
		ptr = find_quote(str);
		if (!ptr)
			break;
		q = *ptr;
		result = str_join(ms, result, str_sub(ms, VOLATILE, str, ptr - str), VOLATILE);
		str = ptr;
	}
	result = str_join(ms, result, str, VOLATILE);
	printf("%s\n", result);
	*src = result;
}
