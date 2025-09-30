/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:44:17 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/24 12:58:45 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

bool	is_builtin(t_cmd *command) //the parameter/member format depends on parser output
{
	return (command->builtin_cmd == ECHO
		|| command->builtin_cmd == CD
		|| command->builtin_cmd == PWD
		|| command->builtin_cmd == EXPORT
		|| command->builtin_cmd == UNSET
		|| command->builtin_cmd == ENV
		|| command->builtin_cmd == EXIT);
}


//could ALSO have a linked list that just points to the very same pointers that are the char **envp,
//and the linked list would be used to directly access and modify **envp.
char	*seek_value(char *env_var)
{
	char	*ptr;

	while (env_var[i])
	{
		if (env_var[i] == '=')
			return (&env_var[i]);
	}
	return (NULL);
}

void	delete_env(char *env_var)
{
	return (SUCCESS);
}

void	append_to_env(char *env_var)
{
	return (SUCCESS);
}
