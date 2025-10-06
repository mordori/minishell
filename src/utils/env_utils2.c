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

t_env	**envll_findkey(t_state *state, char *key)
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

bool	is_valid_key(const char *key, char *delimiter)
{
	bool	is_valid;
	char	c;
	int		i;

	is_valid = true;
	if (key[0] == '\0')
		is_valid = false;
	if (ft_isdigit(key[0]))
		is_valid = false;
	i = 0;
	while (key[i] && is_valid)
	{
		if (!is_valid_identifier(key[i]))
		{
			if (key[i] == '+' && key[i + 1] == '\0' && delimiter)
				break ;
			is_valid = false;
		}
		i++;
	}
	return (is_valid);
}

static bool	is_valid_identifier(const char c)
{
	return (ft_isalnum(c) || c == '_' || c == '=');
}

bool	replace_value(t_env **var, char *value)
{
	(*var)->value = value;
	return (true);
}

int	warning_identifier()
{

}
