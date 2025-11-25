/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:26:59 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/25 02:44:49 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "cleanup.h"
#include "errors.h"
#include "file_utils.h"

static inline bool	is_numbers(const char *str, int *i);
static inline void	warn_numeric(t_minishell *ms, const char *arg);
static inline bool	is_valid(t_minishell *ms, const char *a, uint8_t *status);

int	exi(t_minishell *ms, t_node *node)
{
	uint8_t	status;

	if (ms->mode == INTERACTIVE)
		try_write_endl(ms, STDOUT_FILENO, "exit");
	status = ms->state.exit_status;
	if (node)
	{
		if (node->cmd.args[1])
		{
			if (is_valid(ms, node->cmd.args[1], &status) == false)
				status = ERROR_BUILTIN;
			else if (node->cmd.args[2])
			{
				errno = 0;
				warning(ms, "exit: too many arguments");
				return (ERROR_GENERAL);
			}
		}
	}
	clean(ms);
	exit((uint8_t)status);
}

static inline bool	is_valid(t_minishell *ms, const char *a, uint8_t *status)
{
	int		i;

	i = 0;
	if (is_numbers(a, &i) == false || !*a)
	{
		warn_numeric(ms, a);
		return (false);
	}
	if (i > 20)
	{
		warn_numeric(ms, a);
		return (false);
	}
	else
	{
		i = ft_atoi(a);
		i %= 256;
		*status = (uint8_t)i;
	}
	return (true);
}

static inline bool	is_numbers(const char *str, int *i)
{
	if (str[0] == '-' || str[0] == '+')
	{
		(*i)++;
		if (!str[*i])
			return (false);
	}
	while (str[*i])
	{
		if (ft_isdigit(str[*i]) == false)
			return (false);
		(*i)++;
	}
	return (true);
}

static inline void	warn_numeric(t_minishell *ms, const char *arg)
{
	errno = 0;
	warning(ms, \
str_join(ms, "exit: ", \
str_join(ms, arg, ": numeric argument required", \
VOLATILE), VOLATILE));
}
