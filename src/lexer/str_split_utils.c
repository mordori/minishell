/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 01:10:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/06 21:07:30 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "errors.h"

void	march_operator(char const **src, int *count)
{
	++(*src);
	if (**src && \
((*(*src - 1) == '>' && **src == '>') || (*(*src - 1) == '<' && **src == '<')))
		++(*src);
	++(*count);
}

bool	is_quote_closed(t_minishell *ms, char const **src, char c)
{
	++(*src);
	while (**src && **src != c)
		++(*src);
	if (**src != c)
	{
		warning_input(ms, "unclosed quotes");
		return (true);
	}
	++(*src);
	return (false);
}

void	add_src_len(char const **src, size_t *len)
{
	++(*len);
	++(*src);
}

void	march_quoted_word(char const **src, const char c, size_t *len)
{
	add_src_len(src, len);
	while (*src && **src != c)
		add_src_len(src, len);
	add_src_len(src, len);
}
