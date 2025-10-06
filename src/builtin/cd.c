/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/01 16:17:42 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

//still VERIFY ARG SYNTAX
void	cd(t_cmd *cmd, t_state *state)
{
	char	*path;

	path = cmd->args[1]; //arg syntax ?
	if (!path)
	{
		path = getenv("HOME");
		if (!path)
		{
			state->exit_status = ERROR_BUILTIN;
			return ;
		}
	}
	if (chdir(path))
		state->exit_status = ERROR_BUILTIN;
}
