/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:57:56 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/03 01:41:15 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"
#include "libft_str.h"

bool	cmp_strs(const char **types, const char *src)
{
	while (*types)
	{
		if (!ft_strncmp(src, *types, ft_strlen(*types)))
			return (true);
		++types;
	}
	return (false);
}

bool	is_operator(const char *src)
{
	if (is_redirection(src) || is_pipe(src))
		return (true);
	return (false);
}

bool	is_redirection(const char *src)
{
	if (cmp_strs(get_redirections(), src))
		return (true);
	return (false);
}

bool	is_pipe(const char *src)
{
	if (!ft_strncmp(src, "|", 1))
		return (true);
	return (false);
}

bool	is_quote(const char *src)
{
	if (cmp_strs(get_quotes(), src))
		return (true);
	return (false);
}
