/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:23:57 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/01 17:25:42 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	ft_unset(t_cmd *cmd, t_state *state)
{	
	char	*arg;
	int		i;

	i = 1;
	while (argv[i])
	{
		arg = cmd->argv[i];
		while (state->env)
		{
			if (ft_strcmp(arg, state->env->key) == 0)
				remove_value(state->env);
			state->env = state->env->next;
		}
		i++;
	}
}

void	remove_value(t_env *env)
{
	
}

//export apina=banaani
//unset apina
//		--> -
