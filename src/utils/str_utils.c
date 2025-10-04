/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:34:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/03 21:13:50 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_utils.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "arena_utils.h"

char	*str_sub(\
t_minishell *ms, char const *src, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!src)
		return (NULL);
	i = 0;
	if (ft_strlen(src) > start)
		while (src[start + i] && i < len)
			++i;
	sub = alloc_pool(ms, (i + 1) * sizeof(char));
	ft_memcpy(sub, &src[start], i);
	sub[i] = '\0';
	return (sub);
}

char	*str_join(t_minishell *ms, char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = alloc_pool(ms, (len1 + len2 + 1) * sizeof(char));
	ft_memcpy(str, s1, len1);
	ft_memcpy(&str[len1], s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}
