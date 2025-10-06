/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:34:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/06 05:58:14 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_utils.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "libft_utils.h"
#include "arena.h"

char	*str_dup(t_minishell *ms, const char *s)
{
	if (!s)
		return (NULL);
	return (str_sub(ms, s, 0, ft_strlen(s)));
}

char	*str_sub(\
t_minishell *ms, const char *src, unsigned int start, size_t len)
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

char	*str_join(t_minishell *ms, const char *s1, const char *s2)
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

char	**dup_envp_system(t_minishell *ms, char **envp)
{
	char	**dup;
	size_t	count;
	size_t	len;
	size_t	i;

	if (!envp)
		return (NULL);
	arena_reset(&ms->system);
	count = 0;
	while (envp[count])
		++count;
	dup = alloc_system(ms, (count + 1) * sizeof(*dup));
	i = 0;
	while (i < count)
	{
		len = ft_strlen(envp[i]);
		dup[i] = alloc_system(ms, (len + 1) * sizeof(char));
		if (!dup[i])
			break;
		ft_memcpy(dup[i], envp[i], len + 1);
		++i;
	}
	dup[i] = NULL;
	return (dup);
}

char	*int_to_str(t_minishell *ms, int n)
{
	char		*str;
	size_t		digits;
	int64_t		num;

	num = n;
	if (n < 0)
		num = -(int64_t)num;
	digits = ft_countdigits(num, 10) + (n < 0);
	str = alloc_pool(ms, digits + 1);
	str[digits] = '\0';
	while (digits--)
	{
		str[digits] = '0' + num % 10;
		num /= 10;
	}
	if ((n < 0))
		str[0] = '-';
	return (str);
}
