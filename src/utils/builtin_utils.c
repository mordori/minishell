/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:44:17 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/06 17:26:41 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

// might as well be moved to str_utils2.c once that exists
bool	is_pluschar(char *var, char delimiter)
{
	bool	is_pluschar;
	int		i;

	i = 0;
	is_pluschar = false;
	while (var[i] && var[i] != delimiter)
	{
		if (var[i] == '+')
			is_pluschar = true;
		i++;
	}
	return (is_pluschar);
}
