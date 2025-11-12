/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:23:57 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/12 16:46:25 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	remove_vars(t_minishell *ms, t_env *env, t_node *node);
static void	remove_node(t_minishell *ms, t_env *env);

int	unse(t_minishell *ms, t_node *node)
{
	copy_env_to(VOLATILE, ms);
	arena_reset(&ms->vars);
	remove_vars(ms, ms->state.env, node);
	copy_env_to(PERSISTENT, ms);
	ms->state.envp = envll_to_envp(ms, ms->state.env);
	return (SUCCESS);
}

static int	remove_vars(t_minishell *ms, t_env *env, t_node *node)
{
	char	*arg;
	int		i;

	i = 1;
	while (node->cmd.args[i])
	{
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
