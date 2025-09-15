/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/15 17:34:38 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//still VERIFY ARG SYNTAX
void	cd(t_cmd *cmd, t_state *shell_state)
{
	char	*path;

	path = cmd->args[1]; //arg syntax ?
	if (!path)
	{
		path = getenv("HOME");
		if (!path)
		{
			shell_state->exit_status = ERROR_BUILTIN;
			return ;
		}
	}
	if (chdir(path))
	{
		shell_state->exit_status = ERROR_BUILTIN;
		return ;
	}
}
