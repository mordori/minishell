/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/25 14:42:23 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

//still VERIFY ARG SYNTAX
void	ft_cd(t_cmd *cmd, t_state *state)
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
