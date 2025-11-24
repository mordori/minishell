/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:55:32 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/22 19:19:55 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str_utils.h"
#include "libft_mem.h"

void	update_shlvl(t_minishell *ms, char *delim, char **value)
{
	int		val;
	char	c;
	char	buf[INT32_LENGTH + 1];

	ft_memset(buf, 0, INT32_LENGTH + 1);
	val = ft_strtol(delim, &c);
	if (c)
	{
		*value = str_dup(ms, "1", PERSISTENT);
		return ;
	}
	++val;
	int_to_str((int)val, buf);
	*value = str_dup(ms, buf, PERSISTENT);
}
