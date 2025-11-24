/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:55:32 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/24 19:45:03 by myli-pen         ###   ########.fr       */
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
	if (c || !isatty(STDIN_FILENO))
	{
		if (!isatty(STDIN_FILENO))
			errno = 0;
		*value = str_dup(ms, "1", PERSISTENT);
		return ;
	}
	++val;
	int_to_str((int)val, buf);
	*value = str_dup(ms, buf, PERSISTENT);
}
