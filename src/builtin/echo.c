/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:12 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/23 23:18:07 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "io.h"

/*
	* bash takes multiple arguments into echo and joins them with a space
	* puts a newline instead of space after last arg, BUT NOT WITH OPTION -n
*/

//FIXME: ADD SUPPORT FOR OPTION -n !!!!!!!!!!!!!!!!!!!!
void	echo(t_minishell *ms)
{
	char	*string;
	bool	in_between;
	int		i;
	int		fd;

	i = 1;
	fd = ms->node->pipe_fds[1];
	in_between = false;
	while (ms->node->cmd.args[i])
	{
		if (in_between)
			try_write(ms, fd, " ");
		string = ms->node->cmd.args[i];
		try_write(ms, fd, string);
		if (!in_between)
			in_between = true;
		i++;
	}
	try_write(ms, fd, "\n");
}
