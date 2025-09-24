/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:12 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/15 17:34:40 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
	* bash takes multiple arguments into echo and joins them with a space 
	* it can also take variables of different types (WIP)
	* puts a newline instead of space after last arg
*/
int	echo(t_state *shell, t_cmd *cmd)
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
		ft_printf("%s", string);
		if (!in_between)
			in_between = true;
		i++;
	}
	write(1, "\n", 1);
}
