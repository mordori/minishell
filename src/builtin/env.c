/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:07:03 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/22 16:47:18 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "file_utils.h"

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
		{
			if (*env->value)
			{
				try_write(ms, STDOUT_FILENO, env->key);
				try_write(ms, STDOUT_FILENO, "=");
				try_write_endl(ms, STDOUT_FILENO, env->value);
			}
		}
		env = env->next;
	}
	return (SUCCESS);
}
