/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_transfer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:04:37 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/04 11:08:19 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	copy_to_arena(t_minishell *ms, t_env **head, t_arena_type type);

void	copy_env_to(t_arena_type to_type, t_minishell *ms)
{
	t_env	*env_cpy;

	if (to_type == VOLATILE)
		copy_to_arena(ms, &env_cpy, VOLATILE);
	if (to_type == PERSISTENT)
		copy_to_arena(ms, &env_cpy, PERSISTENT);
	ms->state.env = env_cpy;
}

static void	copy_to_arena(t_minishell *ms, t_env **head, t_arena_type type)
{
	t_env	*var;
	char	*key;
	char	*value;

	*head = NULL;
	while (ms->state.env)
	{
		key = str_dup(ms, ms->state.env->key, type);
		value = str_dup(ms, ms->state.env->value, type);
		var = ft_envnode_new(ms, key, value, type);
		ft_envadd_back(head, var);
		ms->state.env = ms->state.env->next;
	}
}
