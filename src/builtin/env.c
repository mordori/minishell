/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:07:03 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/30 12:29:04 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/* this is what it would look like with t_env *env linked list;
	* but char **envp might be better since execve needs it as **envp
void	ft_env(t_cmd *cmd, t_state *state)
{
	t_env		*env;

	(void) cmd;
	env = state->env;
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}
*/


void	ft_env(t_cmd *cmd, t_state *state)
{
	char	**env_vars;
	char	*var;
	int		ret_value;
	int		i;

	env_vars = state->envp;
	while (env_vars[i])
	{
		var = env_vars[i];
		ret_value = printf("%s\n", var);
		if (ret_value == -1)
			state->exit_status = ERROR_BUILTIN;
		i++;
	}
}
