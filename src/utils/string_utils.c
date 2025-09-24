/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:34:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/24 02:31:30 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_utils.h"

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
