/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:14:16 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/02 19:25:00 by jvalkama         ###   ########.fr       */
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
	t_env	*env;
	int		i;

	env = NULL;
	while (envp[i])
	{
		var_to_node(envp[i], env, false);
		i++;
	}
	state->env = &env;
	return (SUCCESS);
}

void	var_to_node(char *var, t_env *env)
{
	char	*key;
	char	*value;
	char	*delimiter;

	delimiter = ft_strchr(var, '=');
	key = ft_keydup(var, delimiter);
	value = str_dup(delimiter + 1);
	if (!value)
		ft_envadd_back(&env, ft_envnode_new(key, ""));
	else
		ft_envadd_back(&env, ft_envnode_new(key, value));
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
