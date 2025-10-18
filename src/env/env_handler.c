/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:14:16 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/17 17:37:43 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*ALSO: Bourne-style shells support the syntax

           NAME=value command

       to create an environment variable definition only in the scope of
       the process that executes command.
*/
#include "env.h"
#include "arena.h"
#include "str_utils.h"

int	envp_to_envll(t_minishell *ms, char **envp, t_state *state)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		var_to_node(ms, envp[i], env);
		i++;
	}
	state->env = env;
	return (SUCCESS);
}

void	var_to_node(t_minishell *ms, char *var, t_env *env)
{
	char	*key;
	char	*value;
	char	*delimiter;

	delimiter = ft_strchr(var, '=');
	key = ft_keydup(ms, var, delimiter);
	value = str_dup(ms, delimiter + 1);
	if (!value)
		ft_envadd_back(&env, ft_envnode_new(ms, key, ""));
	else
		ft_envadd_back(&env, ft_envnode_new(ms, key, value));
}

char	**envll_to_envp(t_minishell *ms, t_env *env)
{
	char			**envp_copy;
	char			*env_var;
	unsigned int	var_count;
	unsigned int	i;

	i = 0;
	var_count = count_variables(env);
	envp_copy = alloc_volatile(ms, (var_count + 1) * sizeof(void *));
	while (i < var_count)
	{
		env_var = alloc_volatile(ms, ft_strlen((env->key) + ft_strlen(env->value) + 2) * sizeof(char));
		join_keyvalue(env->key, env->value, env_var);
		envp_copy[i] = env_var;
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}
