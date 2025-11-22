/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:44:17 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/22 18:01:43 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

static void	parse_export(t_minishell *ms, char *var, t_key_value *kv);
static bool	handle_specials(t_minishell *ms, char *var, char *key, char *value);

bool	is_pluschar(char *var, char delimiter)
{
	bool	is_pluschar;
	int		i;

	i = 0;
	is_pluschar = false;
	while (var[i] && var[i] != delimiter)
	{
		if (var[i] == '+')
			is_pluschar = true;
		i++;
	}
	return (is_pluschar);
}

bool	handle_cases(t_minishell *ms, int i, t_env *env, t_key_value *kv)
{
	parse_export(ms, ms->node->cmd.args[i], kv);
	if (!is_valid_key(kv->k, kv->delimiter))
	{
		errno = 0;
		warning(ms, str_join(ms, kv->k, ": not a valid identifier", VOLATILE));
		ms->state.exit_status = ERROR_GENERAL;
		return (true);
	}
	if (!kv->delimiter)
	{
		ft_envadd_back(&env, ft_envnode_new(ms, kv->k, NULL, VOLATILE));
		return (true);
	}
	if (handle_specials(ms, ms->node->cmd.args[i], kv->k, kv->value))
	{
		return (true);
	}
	return (false);
}

static void	parse_export(t_minishell *ms, char *var, t_key_value *kv)
{
	kv->value = NULL;
	kv->delimiter = ft_strchr(var, '=');
	kv->k = ft_keydup(ms, var, kv->delimiter);
	if (!kv->delimiter)
		return ;
	kv->value = str_dup(ms, kv->delimiter + 1, VOLATILE);
}

static bool	handle_specials(t_minishell *ms, char *var, char *key, char *value)
{
	bool	is_additive;
	char	*combin_val;
	t_env	*existing_var;

	if (!value)
	{
		ft_envadd_back(&ms->state.env, ft_envnode_new(ms, key, "", VOLATILE));
		return (true);
	}
	is_additive = is_pluschar(var, '=');
	existing_var = envll_findkey(&ms->state, key);
	if (existing_var)
	{
		if (is_additive)
		{
			combin_val = str_join(ms, existing_var->value, value, VOLATILE);
			replace_value(existing_var, combin_val);
			return (true);
		}
		if (replace_value(existing_var, value))
			return (true);
	}
	return (false);
}

int	handle_cd_specs(t_minishell *ms, char **path, bool is_1st_cd)
{
	if (**path == '~')
	{
		if (!envll_findkey(&ms->state, "HOME"))
		{
			errno = 0;
			warning(ms, "cd: HOME not set");
			return (ERROR_GENERAL);
		}
		*path = *path + 1;
		if (**path)
		{
			*path = str_join(ms, \
envll_findkey(&ms->state, "HOME")->value, *path, VOLATILE);
		}
		else
			*path = envll_findkey(&ms->state, "HOME")->value;
	}
	else if (**path == '-')
	{
		if (get_opwd(ms, path, is_1st_cd))
			return (ERROR_GENERAL);
	}
	return (SUCCESS);
}
