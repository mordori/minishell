/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 01:06:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/07 02:49:15 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "str_utils.h"
#include "arena.h"
#include "libft_utils.h"

static inline int		count_words(t_minishell *ms, char const *s);
static inline size_t	word_length(char const **s);

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
		while (*src)
		{
			if (ft_isspace(*src) || is_operator(src))
				break ;
			if (is_unclosed_quote(ms, &src))
				return (ERROR);
			++src;
		}
		if (*src || !ft_isspace(*(src - 1)))
			++count;
	}
	return (count);
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
		return (len);
	}
	while (**src)
	{
		if (ft_isspace(**src) || is_operator(*src))
			break;
		if (cmp_strs(get_quotes(), *src))
			march_quoted_word(src, **src, &len);
		else
			add_src_len(src, &len);
	}
	return (len);
}
