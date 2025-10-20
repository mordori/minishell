/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:25:46 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/17 17:40:30 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_utils.h"

static void	display_exporting_vars(t_state *state);
static void	put_var_into_env(t_minishell *ms);
static void	parse_export(t_minishell *ms, char *var, t_key_value *kv, char **delimiter);
static bool	handle_specials(t_minishell *ms, char *var, char *key, char *value);

void	export(t_minishell *ms)
{
	printf("final node key: %s, value: %s\n", envlast(ms->state.env)->key, envlast(ms->state.env)->value);
	if (!ms->node->cmd.args[1])
		display_exporting_vars(&ms->state);
	else
		put_var_into_env(ms);
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
		if (head->value == NULL)
			printf("declare -x %s\n", head->key);
		else
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
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
			warning(ms, NULL); //NOTE: BREAK HERE? also ask mika about error message. "Invalid identifier."
		if (!delimiter)
			ft_envadd_back(&env, ft_envnode_new(ms, kv.key, NULL));
		is_handled = handle_specials(ms, ms->node->cmd.args[i], kv.key, kv.value);
		if (is_handled)
		{
			i++;
			continue ;
		}
		ft_envadd_back(&env, ft_envnode_new(ms, kv.key, kv.value));
		printf("Added variable: %s=%s\n", kv.key, kv.value);
		printf("final node key: %s, value: %s\n", envlast(env)->key, envlast(env)->value);
		i++;
	}
	ms->state.envp = envll_to_envp(ms, env);
}

static void	parse_export(t_minishell *ms, char *var, t_key_value *kv, char **delimiter)
{
	*delimiter = ft_strchr(var, '=');
	kv->key = ft_keydup(ms, var, *delimiter);
	if (!delimiter)
		return ;
	kv->value = str_dup(ms, *delimiter + 1);
}

static bool	handle_specials(t_minishell *ms, char *var, char *key, char *value)
{
	bool	is_additive;
	char	*combin_val;
	t_env	*existing_key;

	if (!value)
	{
		ft_envadd_back(&ms->state.env, ft_envnode_new(ms, key, ""));
		return (true);
	}
	is_additive = is_pluschar(var, '=');
	existing_key = envll_findkey(&ms->state, key); //NOTE: during testing, make sure this can directly modify value in place
	if (existing_key)
	{
		if (is_additive)
		{
			combin_val = str_join(ms, existing_key->key, value);
			existing_key->value = combin_val;
			return (true);
		}
		if (replace_value(existing_key, value))
			return (true);
	}
	return (false);
}

	//EXPORT WITH ARGS:
	//export name=value
//		export	->	declare -x name="value"
//
//		export name
//		-> name
//
//		export name=
//		-> name=""
//
//		export name=value1 value2
//		-> name="value1"
//		   value2
//
//		export name="value1 value2"
//		-> name="value1 value2"


	// EXPORT WITHOUT ARGS:
	// lists in alphabetical order like: declare -x HOME="/path/"
	// export accepts variable names starting with _ or alphabet (_ape or ape) but not number.
	// Number can be in middle but not first character.
	// variable names in smaller case come AFTER those in upper case, still in alphabetical order.
