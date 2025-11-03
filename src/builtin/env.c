/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:07:03 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/03 17:58:19 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "io.h"

int	env(t_minishell *ms, t_node *node)
{
	t_env	*env;

	env = ms->state.env;
	while (env)
	{
		if (env->value != NULL)
		{
			if (*env->value)
			{
				try_write(ms, node->cmd.out, env->key);
				try_write(ms, node->cmd.out, "=");
				try_write_endl(ms, node->cmd.out, env->value);
			}
		}
		env = env->next;
	}
	return (SUCCESS);
}
