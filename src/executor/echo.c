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
	* it can also take variables of different types
	* puts a newline instead of space after last arg
*/

int	echo(t_state *shell, t_cmd *cmd)
{
	char		*string;
	int			i;

	i = 1;
	while cmd->args[i]
	{
		string = cmd->args[i]; //most likely
		ft_printf("%s", string);
		i++;
	}
	write(1, "\n", 1);
}
