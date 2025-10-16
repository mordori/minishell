/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:12 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/01 16:17:37 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
	* bash takes multiple arguments into echo and joins them with a space 
	* it can also take variables of different types (WIP)
	* puts a newline instead of space after last arg
*/
void	echo(t_cmd *cmd, t_state *state)
{
	char		*string;
	bool		in_between;
	int			i;

	i = 1;
	in_between = false;
	while (cmd->args[i])
	{
		if (in_between)
			write(1, ' ', 1);
		string = cmd->args[i];
		printf("%s", string);
		if (!in_between)
			in_between = true;
		i++;
	}
	write(1, "\n", 1);
}
