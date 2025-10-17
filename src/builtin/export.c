/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:25:46 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/02 19:24:56 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	display_exporting_vars(t_state *state);
static void	put_var_into_env(t_state *state, t_cmd *cmd);
static int	parse_export(char *var, char **key, char **value, char **delimiter);
static bool	handle_specials(t_state *state, char *var, char *key, char *value);

void	export(t_cmd *cmd, t_state *state)
{
	if (!cmd->args[1])
		display_exporting_vars(state);
	else
		put_var_into_env(state, cmd);
}

static void	display_exporting_vars(t_state *state)
{
	t_env		*head;
	t_env		*last;

	head = state->env;
	last = (t_env *) ft_lstlast((t_list *) state->env); //NOTE: the casts here might fuck things up. or at least they are not elegant.
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

static void	put_var_into_env(t_state *state, t_cmd *cmd)
{
	char	*key;
	char	*value;
	char	*delimiter;
	bool	is_handled;
	int		i;
	
	i = 1;
	while (cmd->args[i])
	{
		parse_export(cmd->args[i], &key, &value, &delimiter);
		if (!is_valid_key(key, delimiter))
			warning(ms, NULL); //NOTE: BREAK HERE? also ask mika about error message. "Invalid identifier."
		if (!delimiter)
			ft_envadd_back(state->env, ft_envnode_new(key, NULL));
		is_handled = handle_specials(state, cmd->args[i], key, value);
		if (is_handled)
		{
			i++;
			continue ;
		}
		ft_envadd_back(&env, ft_envnode_new(key, value));
		i++;
	}
	state->envp = envll_to_envp(state->env); //FIX: where the fok is this function these days anyway
}

static int	parse_export(char *var, char **key, char **value, char **delimiter)
{
	*delimiter = ft_strchr(var, '=');
	*key = ft_keydup(var, delimiter);
	if (!delimiter)
		return (0);
	*value = str_dup(delimiter + 1);
}

static bool	handle_specials(t_state *state, char *var, char *key, char *value)
{
	bool	is_additive;
	char	*combin_val;
	t_env	**existing_key;

	if (!value)
	{
		ft_envadd_back(state->env, ft_envnode_new(key, ""));
		return (true);
	}
	is_additive = is_pluschar(var, '=');
	existing_key = envll_findkey(state, key); //NOTE: during testing, make sure this can directly modify value in place
	if (existing_key)
	{
		if (is_additive)
		{
			combin_val = str_join(existing_key->value, value);
			(*existing_key)->value = combin_var;
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
