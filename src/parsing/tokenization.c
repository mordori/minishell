/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 01:06:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/20 17:52:24 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "str_utils.h"
#include "arena.h"
#include "libft_utils.h"
#include "libft_str.h"

static inline int		count_words(t_minishell *ms, char const *s);
static inline size_t	word_length(char const **s);

char	**tokenize(t_minishell *ms, char const *src)
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
	strs = alloc_volatile(ms, sizeof(char *) * (words + 1));
	i = 0;
	while (i < words)
	{
		word_len = word_length(&src);
		strs[i] = str_sub(ms, VOLATILE, src - word_len, word_len);
		++i;
	}
	strs[i] = NULL;
	return (strs);
}

static inline int	count_words(t_minishell *ms, char const *src)
{
	int	count;

	count = 0;
	while (*src)
	{
		while (*src && is_space(*src))
			++src;
		if (is_operator(src) || *src == '\n')
		{
			if (is_unsupported_char(ms, src))
				return (ERROR);
			++count;
			src += 1 + (*(src + 1) && \
((*src == '>' && *(src + 1) == '>') || (*src == '<' && *(src + 1) == '<')));
			continue ;
		}
		while (*src && *src != '\n' && !is_space(*src) && !is_operator(src))
		{
			if (is_unsupported_char(ms, src) || is_unclosed_quote(ms, &src))
				return (ERROR);
			++src;
		}
		if (*src || !is_space(*(src - 1)))
			++count;
	}
	return (count);
}

static inline size_t	word_length(char const **src)
{
	size_t	len;

	len = 0;
	while (**src && is_space(**src))
		++(*src);
	if (is_operator(*src) || **src == '\n')
	{
		add_src_len(src, &len);
		if (*src && \
((*(*src - 1) == '>' && **src == '>') || (*(*src - 1) == '<' && **src == '<')))
			add_src_len(src, &len);
		return (len);
	}
	while (**src && **src != '\n')
	{
		if (is_space(**src) || is_operator(*src))
			break ;
		if (cmp_strs(get_quotes(), *src, NULL))
			march_quoted_word(src, **src, &len);
		else
			add_src_len(src, &len);
	}
	return (len);
}

bool	cmp_strs(const char **types, const char *src, const char **out)
{
	while (*types)
	{
		if (!ft_strncmp(src, *types, ft_strlen(*types)))
		{
			if (out)
				*out = *types;
			return (true);
		}
		++types;
	}
	if (out)
		*out = NULL;
	return (false);
}
