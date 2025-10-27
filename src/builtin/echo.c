/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:12 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/27 12:38:51 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "io.h"

static void	is_newline_off(t_minishell *ms, int *i, bool *is_nl_off);

int	echo(t_minishell *ms)
{
	char	*string;
	bool	is_inbetween;
	bool	is_nl_off;
	int		i;
	//int		fd;

	i = 1;
	//fd = ms->node->pipe_fds[1];
	is_inbetween = false;
	is_newline_off(ms, &i, &is_nl_off);
	while (ms->node->cmd.args[i])
	{
		if (is_inbetween)
			try_write(ms, 1, " ");
		string = ms->node->cmd.args[i];
		try_write(ms, 1, string);
		if (!is_inbetween)
			is_inbetween = true;
		i++;
	}
	if (!is_nl_off)
		try_write(ms, 1, "\n");
	return (SUCCESS);
}

static void	is_newline_off(t_minishell *ms, int *i, bool *is_nl_off)
{
	*is_nl_off = false;
	if (ft_strcmp(ms->node->cmd.args[*i], "-n") == 0)
	{
		*is_nl_off = true;
		(*i)++;
	}
}
