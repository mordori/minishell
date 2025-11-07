/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:12 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/07 11:37:50 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "io.h"

static void	is_newline_off(t_node *node, int *i, bool *is_nl_off);

int	echo(t_minishell *ms, t_node *node)
{
	char	*string;
	bool	is_inbetween;
	bool	is_nl_off;
	int		i;
	int		fd;

	i = 1;
	fd = node->cmd.out;
	is_inbetween = false;
	is_newline_off(node, &i, &is_nl_off);
	while (node->cmd.args[i])
	{
		if (is_inbetween)
			try_write(ms, fd, " ");
		string = node->cmd.args[i];
		try_write(ms, fd, string);
		if (!is_inbetween)
			is_inbetween = true;
		i++;
	}
	if (!is_nl_off)
		try_write(ms, fd, "\n");
	return (SUCCESS);
}

static void	is_newline_off(t_node *node, int *i, bool *is_nl_off)
{
	int			j;
	char		**args;

	*is_nl_off = false;
	args = node->cmd.args;
	if (!args[*i])
		return ;
	while (ft_strncmp(args[*i], "-n", 2) == 0)
	{
		j = 2;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] != 'n' && args[*i][j] != '\0')
			break ;
		*is_nl_off = true;
		(*i)++;
	}
}
