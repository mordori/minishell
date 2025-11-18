/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:52:32 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/18 18:54:14 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "str_utils.h"
#include "arena_list.h"
#include "arena.h"
#include "env.h"

// char	*remove_quotes(t_minishell *ms, char *src)
// {
// 	char	*result;
// 	char	*quote;
// 	size_t	i;

// 	quote = find_quote(src);
// 	if (!quote)
// 		return (src);
// 	i = quote - src;
// 	result = alloc_volatile(ms, i + 1);
// 	ft_memcpy(result, src, i);
// 	while (*src)
// 	{
// 		i = 0;
// 		src = quote + 1;
// 		while (src[i] != *quote)
// 			++i;
// 		result = str_join(ms, result, str_sub(ms, VOLATILE, src, i), VOLATILE);
// 		if (!*(src + 1))
// 			break ;
// 		quote = find_quote(src);
// 		if (!quote)
// 			break ;
// 		result =
// str_join(ms, result, str_sub(ms, VOLATILE, src, quote - src), VOLATILE);
// 	}
// 	result = str_join(ms, result, src, VOLATILE);
// 	return (result);
// }
char	*remove_quotes(t_minishell *ms, char *src)
{
	char	*result;
	char	*quote;
	size_t	i;
	size_t	k;
	bool	is_double;

	is_double = false;
	quote = locate_quote(src);
	if (!quote)
		return (src);
	i = quote - src;
	result = alloc_volatile(ms, i + 1);
	ft_memcpy(result, src, i);
	while (*src)
	{
		i = 0;
		k = 1;
		if (*quote == \
'\"' && *(quote + 1) == '\'' && *(quote + 2) && *(quote + 2) == '\"')
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
			break ;
		quote = locate_quote(src + (k == 2));
		if (!quote)
			break ;
		result = \
str_join(ms, result, str_sub(ms, VOLATILE, src, quote - src), VOLATILE);
	}
	result = str_join(ms, result, src, VOLATILE);
	return (result);
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
