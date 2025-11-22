/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:41:46 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/22 19:05:32 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_utils.h"
#include "libft_str.h"

bool	is_whitespace(const char *src, const char *ifs)
{
	if (!*ifs)
		ifs = get_ifs();
	while (*ifs)
	{
		if (*src == *ifs)
			return (true);
		++ifs;
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
