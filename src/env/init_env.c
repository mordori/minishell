/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:44:05 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/25 15:02:02 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// PARSER
//would need something to parse the *envp argument, 
//and split to keys and values in a t_env stuct for example.
//struct would make it clearer.
void	init_env(t_minishell *ms, char **envp)
{
	chr		*env_var;
	int		i;
	int		j;

	while (envp[i])
	{
		env_var = envp[i];
		parse(env_var);
	}
}

//skeleton draft. AN example.
void	parse(char *env_var)
{
	char		*string;
	t_env		*env;

	env = ms->state->env; //only as long as state is included in ms ofc.
	while (env_var[j])
	{
		env->key = ;
		env->value = ;
	}
}
