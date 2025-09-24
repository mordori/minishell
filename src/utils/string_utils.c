/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:34:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/24 20:13:01 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_utils.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "libft_utils.h"
#include "mem_arena.h"

static inline size_t	ft_count_words(char const *s);
static inline size_t	ft_word_len(char const **s);

/**
 * @brief Converts an signed 64-bit integer to a string.
 *
 * @param n Signed 64-bit integer to convert.
 * @param buf Buffer where the string result is written.
 *
 * @return The number of characters written.
 */
size_t	int_to_str(int n, char *buf)
{
	char	temp[INT32_LENGTH];
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (!n)
		buf[i++] = '0';
	if (n < 0)
		buf[i++] = '-';
	if (n < 0)
		n = -n;
	k = 0;
	while (n > 0)
	{
		temp[k++] = '0' + (n % 10);
		n /= 10;
	}
	j = 0;
	while (j < k)
	{
		buf[i + j] = temp[k - j - 1];
		++j;
	}
	return (i + k);
}

/**
 * Allocates memory and returns an array of strings by splitting string `s`
 * using whitespace characters deliters.
 *
 * Last element is a NULL pointer.
 *
 * @param s Source string.
 * @return New array of strings split from the string `s`.
 */
char	**str_split(char const *src, t_mem_arena *arena)
{
	char	**strs;
	size_t	words;
	size_t	word_len;
	size_t	i;

	if (!src)
		return (NULL);
	words = ft_count_words(src);
	strs = arena_alloc(arena, (words + 1) * sizeof (char *));
	if (!strs)
		return (NULL);
	i = 0;
	while (words--)
	{
		word_len = ft_word_len(&src);
		strs[i] = str_sub(src - word_len, 0, word_len, arena);
		if (!strs[i++])
			return (NULL);
	}
	strs[i] = NULL;
	return (strs);
}

static inline size_t	ft_count_words(char const *src)
{
	size_t	count;

	count = 0;
	while (*src)
	{
		while (*src && ft_isspace(*src))
			++src;
		while (*src && !ft_isspace(*src))
			++src;
		if (*src || !ft_isspace(*(src - 1)))
			++count;
	}
	return (count);
}

static inline size_t	ft_word_len(char const **src)
{
	size_t	len;

	len = 0;
	while (**src && ft_isspace(**src))
		++*src;
	while (**src && !ft_isspace(**src))
	{
		++len;
		++*src;
	}
	return (len);
}

char	*str_sub(\
char const *src, unsigned int start, size_t len, t_mem_arena *arena)
{
	char	*sub;
	size_t	i;

	if (!src)
		return (NULL);
	i = 0;
	if (ft_strlen(src) > start)
		while (src[start + i] && i < len)
			++i;
	sub = arena_alloc(arena, (i + 1) * sizeof (char));
	if (sub)
	{
		ft_memcpy(sub, &src[start], i);
		sub[i] = '\0';
	}
	return (sub);
}
