/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:23:57 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/03 13:42:45 by jvalkama         ###   ########.fr       */
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
	return (SUCCESS);
}

static int	remove_vars(t_minishell *ms, t_env *env, t_node *node)
{
	char	*arg;
	int		i;
	t_env	*tmp;

	i = 1;
	env = NULL;
	while (node->cmd.args[i])
	{
		tmp = env;
		arg = node->cmd.args[i];
		while (tmp)
		{
			if (ft_strcmp(arg, tmp->key) == 0)
			{
				remove_node(ms, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	ms->state.envp = envll_to_envp(ms, env);
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
