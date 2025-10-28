/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:33:53 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/27 23:57:27 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "str_utils.h"
#include "arena_list.h"
#include "arena.h"
#include "env.h"

void	join_var_name(t_minishell *ms, char **str, char **result, t_expand_mode mode)
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

void	join_var(t_minishell *ms, char **str, char **result, char quote, t_expand_mode mode)
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
