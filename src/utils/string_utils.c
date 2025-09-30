/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:34:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/01 01:19:56 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_utils.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "libft_utils.h"
#include "mem_utils.h"
#include "errors.h"
#include "lexer.h"

static inline int		count_words(t_minishell *ms, char const *s);
static inline size_t	word_length(char const **s);
static inline bool		is_quote_closed(t_minishell *ms, char const **src, char c);

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
	words = count_words(ms, src);
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

static inline int	count_words(t_minishell *ms, char const *src)
{
	size_t	count;

	count = 0;
	while (*src)
	{
		while (*src && ft_isspace(*src))
			++src;
		if (cmp_type(get_redirs(), src) || (cmp_type(get_pipe(), src)))
		{
			++count;
			++src;
			if (*src && \
((*(src - 1) == '>' && *src == '>') || (*(src - 1) == '<' && *src == '<')))
				++src;
			if (*src && *(src - 1) == '<' && *src == '<')
				++src;
			continue ;
		}
		else if (*src == '\'')
		{
			if (!is_quote_closed(ms, &src, '\''))
				return (ERROR);
		}
		else if (*src == '\"')
		{
			if (!is_quote_closed(ms, &src, '\"'))
				return (ERROR);
		}
		else
			while (*src && !ft_isspace(*src) && !cmp_types(src))
				++src;
		if (*src || !ft_isspace(*(src - 1)))
			++count;
	}
	return (count);
}

static inline bool	is_quote_closed(t_minishell *ms, char const **src, char c)
{
	++*src;
	while (**src && **src != c)
		++*src;
	if (**src != c)
	{
		error_input(ms, "unclosed quotes.");
		return (false);
	}
	++*src;
	return (true);
}

static inline size_t	word_length(char const **src)
{
	size_t	len;

	len = 0;
	while (**src && ft_isspace(**src))
		++*src;
	if (cmp_type(get_redirs(), *src) || (cmp_type(get_pipe(), *src)))
	{
		++len;
		++*src;
		if (*src && \
((*(*src - 1) == '>' && **src == '>') || (*(*src - 1) == '<' && **src == '<')))
		{
			++len;
			++*src;
		}
		if (*src && *(*src - 1) == '<' && **src == '<')
		{
			++len;
			++*src;
		}
	}
	else if (**src == '\'')
	{
		++*src;
		while (*src && **src != '\'')
		{
			++len;
			++*src;
		}
		len += 2;
		++*src;
	}
	else if (**src == '\"')
	{
		++*src;
		while (*src && **src != '\"')
		{
			++len;
			++*src;
		}
		len += 2;
		++*src;
	}
	else
	{
		while (**src && !ft_isspace(**src) && !cmp_types(*src))
		{
			++len;
			++*src;
		}
	}
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
