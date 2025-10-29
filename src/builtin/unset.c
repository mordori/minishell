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

static int	remove_vars(t_minishell *ms, t_node *node);
static void	remove_node(t_minishell *ms, t_env *env);

int	unse(t_minishell *ms, t_node *node)
{
	copy_env_to(VOLATILE, ms);
	arena_reset(&ms->vars);
	remove_vars(ms, node);
	copy_env_to(PERSISTENT, ms);
	return (SUCCESS);
}

static int	remove_vars(t_minishell *ms, t_node *node)
{
	char	*arg;
	int		i;
	t_env	*env;

	i = 1;
	while (node->cmd.args[i])
	{
		env = ms->state.env;
		arg = node->cmd.args[i];
		while (env)
		{
			if (ft_strcmp(arg, env->key) == 0)
			{
				remove_node(ms, env);
				break ;
			}
			env = env->next;
		}
		i++;
	}
	return (SUCCESS);
}

static void	remove_node(t_minishell *ms, t_env *env)
{
	t_env	*prior;
	t_env	*latter;

	prior = env->prev;
	latter = env->next;
	if (ms->state.env == env)
		ms->state.env = latter;
	if (prior)
		prior->next = latter;
	if (latter)
		latter->prev = prior;
}
