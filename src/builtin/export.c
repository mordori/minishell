/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:25:46 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/01 19:13:11 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

	//in bash export sets env variables so they are available for child prcesses and extern programas
	//makes a new env variable accessible.
void	ft_export(t_cmd *cmd, t_state *state)
{
	if (!cmd->argv[1])
		display_exported_vars(state);
	else
	{
		var = cmd->argv[1];
		var_to_node(var, state->env);
		state->envp = envll_to_envp(state->env);
	}
}

void	display_exported_vars(t_state *state)
{
	char		**envp;
	size_t		len;
	size_t		i;

	i = 0;
	len = 0;
	envp = state->envp;
	while (envp[len])
		len++;
	quicksort(envp, 0, len - 1);
	while (envp[i])
	{
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		i++;
	}

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
