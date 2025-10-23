/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:12 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/23 16:57:01 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "errors.h"

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
	int		bytes;

	i = 1;
	bytes = 0;
	fd = ms->node->pipe_fds[1];
	in_between = false;
	while (ms->node->cmd.args[i])
	{
		if (in_between)
			bytes = write(fd, " ", 1);
		string = ms->node->cmd.args[i];
		if (bytes != ERROR)
			bytes = write(fd, string, ft_strlen(string));
		if (!in_between)
			in_between = true;
		i++;
	}
	if (bytes != ERROR)
		bytes = write(fd, "\n", 1);
	if (bytes == ERROR)
		error_exit(ms, "write failed");
}
