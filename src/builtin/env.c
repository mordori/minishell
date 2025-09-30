/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:07:03 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/25 14:42:08 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_env(t_cmd *cmd, t_state *state)
{
	t_env		*env;

	(void) cmd;
	env = state->env;
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}
