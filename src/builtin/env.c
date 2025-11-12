/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:07:03 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/04 17:10:25 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "io.h"

int	env(t_minishell *ms, t_node *node)
{
	t_env	*env;

	(void)node;
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
