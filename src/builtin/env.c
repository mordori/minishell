/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:07:03 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/24 15:14:28 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "file_utils.h"

static void	print_env(t_minishell *ms, t_env *env)
{
	int		fd_out;

	fd_out = STDOUT_FILENO;
	if (ms->state.mode == SIMPLE)
		fd_out = ms->node->cmd.redir_out;
	try_write(ms, fd_out, env->key);
	try_write(ms, fd_out, "=");
	try_write_endl(ms, fd_out, env->value);
}

int	env(t_minishell *ms, t_node *node)
{
	t_env	*env;

	if (node->cmd.args[1])
	{
		warning(ms, str_join(ms, "env: ", node->cmd.args[1], VOLATILE));
		return (127);
	}
	env = ms->state.env;
	while (env)
	{
		if (env->value != NULL)
			print_env(ms, env);
		env = env->next;
	}
	return (SUCCESS);
}
