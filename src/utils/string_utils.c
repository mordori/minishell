/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:34:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/02 03:25:25 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_utils.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "libft_utils.h"
#include "arena_utils.h"
#include "errors.h"
#include "lexer.h"

static inline int		count_words(char const *s);
static inline size_t	word_length(char const **s);
static inline void		is_quote_closed(char const **src, char c, int *count);

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
char	**str_split(t_minishell *ms, char const *src)
{
	char	**strs;
	int		words;
	size_t	word_len;
	int		i;

	if (!src)
		return (NULL);
	words = count_words(src);
	if (words == ERROR)
		return (NULL);
	strs = alloc_pool(ms, sizeof(*strs) * (words + 1));
	i = 0;
	while (i < words)
	{
		word_len = word_length(&src);
		strs[i] = str_sub(ms, src - word_len, 0, word_len);
		++i;
	}
	strs[i] = NULL;
	return (strs);
}

static inline void	march_operator(char const **src, int *count)
{
	++(*src);
	if (**src && \
((*(*src - 1) == '>' && **src == '>') || (*(*src - 1) == '<' && **src == '<')))
		++(*src);
	++*count;
}

static inline int	count_words(char const *src)
{
	int	count;

	count = 0;
	while (*src)
	{
		while (*src && ft_isspace(*src))
			++src;
		if (is_operator(src))
		{
			march_operator(&src, &count);
			continue ;
		}
		else if (*src == '\'')
			is_quote_closed(&src, '\'', &count);
		else if (*src == '\"')
			is_quote_closed(&src, '\"', &count);
		else
			while (*src && !ft_isspace(*src) && !is_operator(src) && !is_quote(src))
				++src;
		if (count == ERROR)
			return (ERROR);
		if (*src || !ft_isspace(*(src - 1)))
			++count;
	}
	return (count);
}

static inline void	is_quote_closed(char const **src, char c, int *count)
{
	++(*src);
	while (**src && **src != c)
		++(*src);
	if (**src != c)
	{
		error_input("unclosed quotes");
		*count = ERROR;
		return ;
	}
	++(*src);
}

static inline void	add_src_len(char const **src, size_t *len)
{
	++(*len);
	++(*src);
}

static inline void	march_quote(char const **src, const char c, size_t *len)
{
	add_src_len(src, len);
	while (*src && **src != c)
		add_src_len(src, len);
	add_src_len(src, len);
}

static inline size_t	word_length(char const **src)
{
	size_t	len;

	len = 0;
	while (**src && ft_isspace(**src))
		++(*src);
	if (is_operator(*src))
	{
		add_src_len(src, &len);
		if (*src && \
((*(*src - 1) == '>' && **src == '>') || (*(*src - 1) == '<' && **src == '<')))
			add_src_len(src, &len);
	}
	else if (**src == '\'')
		march_quote(src, '\'', &len);
	else if (**src == '\"')
		march_quote(src, '\"', &len);
	else
		while (**src && !ft_isspace(**src) && !is_operator(*src) && !is_quote(*src))
			add_src_len(src, &len);
	return (len);
}

char	*str_sub(\
t_minishell *ms, char const *src, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!src)
		return (NULL);
	i = 0;
	if (ft_strlen(src) > start)
		while (src[start + i] && i < len)
			++i;
	sub = alloc_pool(ms, (i + 1) * sizeof(char));
	ft_memcpy(sub, &src[start], i);
	sub[i] = '\0';
	return (sub);
}
