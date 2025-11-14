/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:14:16 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/14 11:52:55 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	envp_to_envll(t_minishell *ms, char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		var_to_node(ms, envp[i], &env);
		i++;
	}
	ms->state.env = env;
	return (SUCCESS);
}

void	var_to_node(t_minishell *ms, char *var, t_env **env)
{
	char	*key;
	char	*value;
	char	*delimiter;
	t_env	*node;

	node = NULL;
	delimiter = ft_strchr(var, '=');
	key = ft_keydup(ms, var, delimiter);
	if (ft_strcmp(key, "SHLVL") == 0)
		update_shlvl(ms, delimiter + 1, &value);
	else if (ft_strcmp(key, "SHELL") == 0)
		value = update_shell_value(ms);
	else
		value = str_dup(ms, delimiter + 1, PERSISTENT);
	if (!value)
		node = ft_envnode_new(ms, key, "", PERSISTENT);
	else
		node = ft_envnode_new(ms, key, value, PERSISTENT);
	ft_envadd_back(env, node);
}

char	*update_shell_value(t_minishell *ms)
{
	char		*pwd;
	char		buf[PATH_MAX];
	char		*shell_path;

	pwd = getcwd(buf, sizeof(buf));
	shell_path = str_dup(ms, str_join(ms, \
pwd, "/minishell", VOLATILE), PERSISTENT);
	return (shell_path);
}

char	**envll_to_envp(t_minishell *ms, t_env *env)
{
	char			**envp_copy;
	char			*env_var;
	unsigned int	var_count;
	unsigned int	i;

	i = 0;
	var_count = count_variables(env);
	envp_copy = alloc_vars(ms, (var_count + 1) * sizeof(*envp_copy));
	while (i < var_count)
	{
		env_var = alloc_vars(\
ms, ft_strlen(env->key) + ft_strlen(env->value) + 2);
		if (env->value)
			join_keyvalue(env->key, env->value, env_var);
		else
			join_keyvalue(env->key, "", env_var);
		envp_copy[i] = env_var;
		i++;
		env = env->next;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

char	*get_env_val(t_minishell *ms, char *key)
{
	t_env	*env;

	env = envll_findkey(&ms->state, key);
	if (!env)
		return ("");
	return (env->value);
}
