/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:33:53 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/17 18:02:59 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "str_utils.h"
#include "arena_list.h"
#include "arena.h"
#include "env.h"

static inline char	*trim_spaces(t_minishell *ms, char *src);

void	join_var(t_minishell *ms, char **str, char **result, char *quote, t_expand_mode mode)
{
	size_t		i;
	char		*val;
	char		*name;
	static char	c[2];

	i = 0;
	val = NULL;
	if ((*str)[i] == '$')
	{
		*result = str_join(ms, *result, "$", VOLATILE);
		return ;
	}
	while ((*str)[i] && (*str)[i] != '$' && !is_whitespace(*str + i, ""))
	{
		if (((*str)[i] == '\"' || (*str)[i] == '\''))
			break;
		++i;
	}
	if (!quote || *quote == '\"' || mode == EXPAND_HEREDOC)
	{
		name = str_sub(ms, VOLATILE, *str, i);
		val = get_env_val(ms, name);
		c[0] = '\'' - (*val == '\'') * 5;
		if (mode != EXPAND_HEREDOC && (*val == '\'' || *val == '\"'))
			*result = str_join(ms, *result, c, VOLATILE);
		if (!quote && mode != EXPAND_HEREDOC)
			val = trim_spaces(ms, val);
		*result = str_join(ms, *result, val, VOLATILE);
		if (mode != EXPAND_HEREDOC && (*val == '\'' || *val == '\"'))
			*result = str_join(ms, *result, c, VOLATILE);
	}
	else if (*quote == '\'')
	{
		(*str)--;
		++i;
		val = str_sub(ms, VOLATILE, *str, i);
		*result = str_join(ms, *result, val, VOLATILE);
	}
	*str += i;
}

char	*find_quote(char *str)
{
	char	*single_q;
	char	*double_q;

	single_q = ft_strchr(str, '\'');
	double_q = ft_strchr(str, '\"');
	if (!single_q && !double_q)
		return (NULL);
	if (single_q && (!double_q || single_q < double_q))
		return (single_q);
	else
		return (double_q);
}

static inline char	*trim_spaces(t_minishell *ms, char *src)
{
	char	*result;
	char	*ifs;
	char	*str;
	size_t	i;

	str = src;
	ifs = get_env_val(ms, "IFS");
	i = 0;
	while (*str)
	{
		while (is_whitespace(str, ifs))
			++str;
		if (i > 0 && is_whitespace(str - 1, ifs))
			++i;
		if (*str)
		{
			++i;
			++str;
		}
	}
	result = alloc_volatile(ms, i + 1);
	i = 0;
	str = src;
	while (*str)
	{
		while (is_whitespace(str, ifs))
			++str;
		if (str > src && is_whitespace(str - 1, ifs))
			result[i++] = *(str - 1);
		if (*str)
		{
			result[i++] = *str;
			++str;
		}
	}
	return (result);
}
