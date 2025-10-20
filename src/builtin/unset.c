/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:23:57 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/17 17:20:05 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	remove_node(t_env *env);

void	unset(t_minishell *ms)
{
	char	*arg;
	int		i;
	t_cmd	cmd;
	t_env	*env;

	i = 1;
	cmd = ms->node->cmd;
	while (cmd.args[i])
	{
		env = ms->state.env;
		arg = cmd.args[i];
		while (env)
		{
			if (ft_strcmp(arg, env->key) == 0)
			{
				remove_node(env);
				break ;
			}
			env = env->next;
		}
		i++;
	}
}

static void	remove_node(t_env *env)
{
	t_env	*prior;
	t_env	*latter;

	prior = env->prev;
	latter = env->next;
	if (prior)
		prior->next = latter;
	if (latter)
		latter->prev = prior;
}
