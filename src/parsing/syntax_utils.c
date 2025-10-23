/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:57:56 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/22 13:29:18 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "errors.h"
#include "libft_str.h"
#include "str_utils.h"

bool	is_space(char c)
{
	return (c == ' ' || c == '\t');
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

bool	is_unsupported_char(t_minishell *ms, const char *src)
{
	const char	*c;

	if (cmp_strs(get_unsupported_chars(), src, &c))
	{
		warning(ms, \
str_join(ms, \
str_join(ms, \
"warning: unsupported meta-character `", c, VOLATILE), \
"'", VOLATILE));
		return (true);
	}
	return (false);
}
