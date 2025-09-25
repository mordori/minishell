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

//skeleton draft
void	parse(char *env_var)
{
	char		*string;

	while (env_var[j])
	{
		ms->state->env; //if state included in ms. otherwise could take just state, for example.
		if ()
			env->key = string;
		else
			env->value = string;
	}
}
