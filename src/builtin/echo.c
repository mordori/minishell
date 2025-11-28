/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:12 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/24 19:03:39 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "file_utils.h"

static void	is_newline_off(t_node *node, int *i, bool *is_nl_off);

int	echo(t_minishell *ms, t_node *node)
{
	char	*string;
	bool	is_inbetween;
	bool	is_nl_off;
	int		i;
	int		fd_out;

	fd_out = STDOUT_FILENO;
	if (ms->state.mode == SIMPLE)
		fd_out = ms->node->cmd.redir_out;
	i = 1;
	is_inbetween = false;
	is_newline_off(node, &i, &is_nl_off);
	while (node->cmd.args[i])
	{
		if (is_inbetween)
			try_write(ms, fd_out, " ");
		string = node->cmd.args[i];
		try_write(ms, fd_out, string);
		if (!is_inbetween)
			is_inbetween = true;
		i++;
	}
	if (!is_nl_off)
		try_write(ms, fd_out, "\n");
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
	while (args[*i] && ft_strncmp(args[*i], "-n", 2) == 0)
	{
		j = 2;
		while (args[*i] && args[*i][j] == 'n')
			j++;
		if (args[*i] && args[*i][j] != 'n' && args[*i][j] != '\0')
			break ;
		*is_nl_off = true;
		(*i)++;
	}
}
