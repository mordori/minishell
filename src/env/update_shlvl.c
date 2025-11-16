/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:55:32 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/14 11:55:54 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	update_shlvl(t_minishell *ms, char *delim, char **value)
{
	int		i;

	i = 0;
	*value = str_dup(ms, delim, PERSISTENT);
	while (delim[i])
	{
		if (!ft_isdigit(delim[i]))
		{
			**value = 1;
			return ;
		}
		i++;
	}
	*value[i - 1] += 1;
}
