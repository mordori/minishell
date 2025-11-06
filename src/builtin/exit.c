/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:26:59 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/06 18:48:18 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "cleanup.h"
#include "errors.h"
#include "io.h"

static inline bool	is_numbers(char *str);

int	exi(t_minishell *ms, t_node *node)
{
	int	status;

	(void) node;
	try_write_endl(ms, STDOUT_FILENO, "exit");
	status = ms->state.exit_status;
	if (node->cmd.argc > 2)
	{
		warning(ms, "exit: too many arguments");
		return (ERROR_GENERAL);
	}
	if (node->cmd.args[1])
	{
		if (is_numbers(node->cmd.args[1]) == false)
			warning(ms, \
str_join(ms, "exit: ", \
str_join(ms, node->cmd.args[1], ": numeric argument required", \
VOLATILE), VOLATILE));
		else
			status = ft_atoi(node->cmd.args[1]);
	}
	clean(ms);
	exit(status);
}

static inline bool	is_numbers(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
