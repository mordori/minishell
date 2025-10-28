/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:23:57 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/28 10:50:53 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	remove_node(t_env *env);
static int	remove_vars(t_minishell *ms);

int	unse(t_minishell *ms)
{
	copy_env_to(VOLATILE, ms);
	arena_reset(&ms->vars);
	remove_vars(ms);
	copy_env_to(PERSISTENT, ms);
	return (SUCCESS);
}

static int	remove_vars(t_minishell *ms)
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
	return (SUCCESS);
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
