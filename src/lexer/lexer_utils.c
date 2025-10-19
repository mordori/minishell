/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:57:56 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/19 05:50:12 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "errors.h"
#include "libft_str.h"

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

bool	is_operator(const char *src)
{
	if (is_redirection(src) || is_pipe(src))
		return (true);
	return (false);
}

bool	is_redirection(const char *src)
{
	if (cmp_strs(get_redirections(), src, NULL))
		return (true);
	return (false);
}

bool	is_pipe(const char *src)
{
	if (!ft_strncmp(src, "|", 1))
	{
		if (!ft_strncmp(src + 1, "|", 1))
			return (false);
		return (true);
	}
	return (false);
}

bool	is_newline(const char *src)
{
	if (!ft_strncmp(src, "\n", 1))
		return (true);
	return (false);
}
