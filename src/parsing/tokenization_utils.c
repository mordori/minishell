/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 01:10:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/18 19:00:31 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "errors.h"
#include "libft_str.h"
#include "str_utils.h"

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

bool	is_unclosed_quote(t_minishell *ms, const char **src)
{
	char	*closing_quote;

	if (cmp_strs(get_quotes(), *src, NULL))
	{
		closing_quote = ft_strchr(*src + 1, **src);
		if (closing_quote)
			*src = closing_quote;
		else
		{
			warning(ms, "warning: unexpected end-of-file");
			ms->state.exit_status = 1;
			return (true);
		}
	}
	return (false);
}
