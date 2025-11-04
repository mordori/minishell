/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:44:17 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/04 12:06:19 by jvalkama         ###   ########.fr       */
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

bool	handle_cases(t_minishell *ms, int *i, t_env *env, t_key_value *kv)
{
	parse_export(ms, ms->node->cmd.args[*i], kv);
	if (!is_valid_key(kv->key, kv->delimiter))
		warning(ms, str_join(ms, \
kv->key, ": not a valid identifier", VOLATILE));
	if (!kv->delimiter)
	{
		ft_envadd_back(&env, ft_envnode_new(ms, kv->key, NULL, VOLATILE));
		(*i)++;
		return (true);
	}
	if (handle_specials(ms, \
ms->node->cmd.args[*i], kv->key, kv->value))
	{
		(*i)++;
		return (true);
	}
	return (false);
}

static void	parse_export(t_minishell *ms, char *var, t_key_value *kv)
{
	kv->value = NULL;
	kv->delimiter = ft_strchr(var, '=');
	kv->key = ft_keydup(ms, var, kv->delimiter);
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
