/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:41:46 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/17 20:43:05 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_utils.h"
#include "libft_str.h"

bool	is_whitespace(const char *src, const char *set)
{
	if (!*set)
		set = get_ifs();
	while (*set)
	{
		if (*src == *set)
			return (true);
		++set;
	}
	return (false);
}

char	*str_trim(char *src, const char *set)
{
	size_t	len;

	while (is_whitespace(src, set))
		++src;
	len = ft_strlen(src);
	while (is_whitespace(src + len, set))
		--len;
	src[len] = 0;
	return (src);
}
