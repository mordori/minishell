/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:34:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/05 18:01:13 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_utils.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "libft_utils.h"
#include "arena.h"

char	*str_dup(t_minishell *ms, const char *s, t_arena_type type)
{
	if (!s)
		return (NULL);
	return (str_sub(ms, type, s, ft_strlen(s)));
}

char	*str_sub(\
t_minishell *ms, t_arena_type type, const char *src, size_t len)
{
	char	*sub;
	size_t	i;

	if (!src)
		return (NULL);
	i = 0;
	if (ft_strlen(src) > 0)
		while (src[i] && i < len)
			++i;
	if (type == PERSISTENT)
		sub = alloc_vars(ms, i + 1);
	else
		sub = alloc_volatile(ms, i + 1);
	ft_memcpy(sub, src, i);
	return (sub);
}

char	*str_join(t_minishell *ms, const char *s1, const char *s2, t_arena_type type)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (type == PERSISTENT)
		str = alloc_vars(ms, len1 + len2 + 1);
	else
		str = alloc_volatile(ms, len1 + len2 + 1);
	ft_memcpy(str, s1, len1);
	ft_memcpy(&str[len1], s2, len2);
	return (str);
}

char	*uint_to_str(t_minishell *ms, unsigned int n)
{
	char		*str;
	size_t		digits;
	uint64_t	num;

	num = n;
	digits = ft_ucountdigits(num, 10);
	str = alloc_volatile(ms, digits + 1);
	while (digits--)
	{
		str[digits] = '0' + num % 10;
		num /= 10;
	}
	return (str);
}

char	**str_split(t_minishell *ms, const char *src, char c)
{
	char	**strs;
	size_t	words;
	size_t	word_len;
	size_t	i;

	if (!src)
		return (NULL);
	words = ft_count_words(src, c);
	strs = alloc_volatile(ms, (words + 1) * sizeof(char *));
	i = 0;
	while (words--)
	{
		word_len = ft_word_len(&src, c);
		strs[i] = str_sub(ms, VOLATILE, src - word_len, word_len);
		++i;
	}
	strs[i] = NULL;
	return (strs);
}

bool	is_whitespace(const char *src, const char *set)
{
	if (!*set)
		set = get_ifs();
	while (*set)
	{
		if (*src == *set)
			return (true);
		++set;
	}
	return (false);
}

char	*str_trim(char *src, const char *set)
{
	size_t	len;

	while (is_whitespace(src, set))
		++src;
	len = ft_strlen(src);
	while (is_whitespace(src + len, set))
		--len;
	src[len] = 0;
	return (src);
}
