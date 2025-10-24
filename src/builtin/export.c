/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:25:46 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/24 16:42:42 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_utils.h"

static void	display_exporting_vars(t_state *state);
static void	put_var_into_env(t_minishell *ms);
static void	parse_export(t_minishell *ms, char *var, t_key_value *kv, char **delimiter);
static bool	handle_specials(t_minishell *ms, char *var, char *key, char *value);

int	expo(t_minishell *ms)
{
	if (!ms->node->cmd.args[1])
		display_exporting_vars(&ms->state);
	else
		put_var_into_env(ms);
	return (SUCCESS);
}

static void	display_exporting_vars(t_state *state)
{
	t_env		*head;
	t_env		*last;

	head = state->env;
	last = envlast(state->env);
	quicksort(head, last);
	while (head)
	{
		if (head->value)
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
		else
			printf("declare -x %s\n", head->key);
		head = head->next;
	}
}

static void	put_var_into_env(t_minishell *ms)
{
	t_key_value	kv;
	char		*delimiter;
	bool		is_handled;
	int			i;
	t_env		*env;

	i = 1;
	env = ms->state.env;
	while (ms->node->cmd.args[i])
	{
		parse_export(ms, ms->node->cmd.args[i], &kv, &delimiter);
		if (!is_valid_key(kv.key, delimiter))
			warning(ms, str_join(ms, kv.key, ": not a valid identifier", VOLATILE));
		if (!delimiter)
		{
			ft_envadd_back(&env, ft_envnode_new(ms, kv.key, NULL));
			i++;
			continue ;
		}
		is_handled = handle_specials(ms, ms->node->cmd.args[i], kv.key, kv.value);
		if (is_handled)
		{
			i++;
			continue ;
		}
		ft_envadd_back(&env, ft_envnode_new(ms, kv.key, kv.value));
		i++;
	}
	ms->state.envp = envll_to_envp(ms, env);
}

static void	parse_export(t_minishell *ms, char *var, t_key_value *kv, char **delimiter)
{
	kv->value = NULL;
	*delimiter = ft_strchr(var, '=');
	kv->key = ft_keydup(ms, var, *delimiter);
	if (!*delimiter)
		return ;
	kv->value = str_dup(ms, *delimiter + 1, PERSISTENT);
}

static bool	handle_specials(t_minishell *ms, char *var, char *key, char *value)
{
	bool	is_additive;
	char	*combin_val;
	t_env	*existing_var;

	if (!value)
	{
		ft_envadd_back(&ms->state.env, ft_envnode_new(ms, key, ""));
		return (true);
	}
	is_additive = is_pluschar(var, '=');
	existing_var = envll_findkey(&ms->state, key);
	if (existing_var)
	{
		if (is_additive)
		{
			combin_val = str_join(ms, existing_var->value, value, PERSISTENT);
			replace_value(existing_var, combin_val);
			return (true);
		}
		if (replace_value(existing_var, value))
			return (true);
	}
	return (false);
}
