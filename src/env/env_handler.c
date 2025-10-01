/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:14:16 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/01 16:00:00 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*ALSO: Bourne-style shells support the syntax

           NAME=value command

       to create an environment variable definition only in the scope of
       the process that executes command.
*/
#include "env.h"

int	envp_to_envll(char **envp, t_state *state)
{
	char	*key;
	char	*value;
	char	*delimiter;
	t_env	*env;
	int		i;

	env = NULL;
	while (envp[i])
	{
		delimiter = ft_strchr(envp[i]);
		key = ft_keydup(envp[i], delimiter);
		value = str_dup(delimiter + 1);
		ft_envadd_back(&env, ft_envnode_new(key, value));
		i++;
	}
	state->env = &env;
	return (SUCCESS);
}

char	**envll_to_envp(t_env *env)
{
	char			**envp_copy;
	char			*env_var;
	unsigned int	var_count;
	unsigned int	i;

	i = 0;
	var_count = count_variables(env) 
	envp_copy = alloc_pool((var_count + 1) * sizeof(void *));
	while (i < var_count)
	{
		env_var = alloc_pool(strlen((env->key) + strlen(env->value) + 2) * sizeof(char));
		join_keyvalue(env->key, env->value, &env_var);
		envp_copy[i] = env_var;
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}
