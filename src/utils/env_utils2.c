/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:44:46 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/02 19:25:04 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_env	**find_key(t_state *state, char *key)
{
	t_env	*env;

	env = state->env;
	while (env)
	{
		if (ft_strcmp(env->value, key) == 0)
			return (&env);
		env = env->next;
	}
	return (NULL);
}
