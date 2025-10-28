/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:07:03 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/28 11:29:57 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "io.h"

int	env(t_minishell *ms)
{
	t_env	*env;

	env = ms->state.env;
	while (env)
	{
		if (env->value != NULL)
		{
			if (*env->value)
			{
				try_write(ms, ms->node->pipe_fds[1], env->key);
				try_write(ms, ms->node->pipe_fds[1], "=");
				try_write_endl(ms, ms->node->pipe_fds[1], env->value);
			}
		}
		env = env->next;
	}
	return (SUCCESS);
}
