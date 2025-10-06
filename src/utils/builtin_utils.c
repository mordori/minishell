/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:44:17 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/02 19:25:05 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

bool	is_builtin(t_cmd *cmd)
{
	return (cmd->builtin == ECHO
		|| cmd->builtin == CD
		|| cmd->builtin == PWD
		|| cmd->builtin == EXPORT
		|| cmd->builtin == UNSET
		|| cmd->builtin == ENV
		|| cmd->builtin == EXIT);
}

// might as well be moved to str_utils2.c once that exists
bool	is_pluschar(char *var, char delimiter)
{
	bool	is_pluschar;

	is_pluschar = false;
	while (var[i] && var[i] != delimiter)
	{
		if (var[i] == '+')
			is_pluschar = true;
		i++;
	}
	return (is_pluschar);
}
