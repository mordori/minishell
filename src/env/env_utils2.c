/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:44:46 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/04 12:39:20 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*envll_findkey(t_state *state, char *key)
{
	t_env	*env;

	env = state->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

bool	is_valid_key(const char *key, char *delimiter)
{
	bool	is_valid;
	int		i;

	is_valid = true;
	if (key[0] == '\0')
		is_valid = false;
	if (ft_isdigit(key[0]))
		is_valid = false;
	i = 0;
	while (key[i] && is_valid)
	{
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '=')
		{
			if (key[i] == '+' && key[i + 1] == '\0' && delimiter)
				break ;
			is_valid = false;
		}
		i++;
	}
	return (is_valid);
}

bool	replace_value(t_env *var, char *value)
{
	var->value = value;
	return (true);
}

t_env	*envlast(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

int	count_variables(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
