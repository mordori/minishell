/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/17 17:21:53 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

//FIXME: still VERIFY ARG SYNTAX
void	cd(t_minishell *ms)
{
	char	*path;

	path = ms->node->cmd.args[1]; //FIXME: arg syntax ? esim. "cd -"
	if (!path)
	{
		path = getenv("HOME");
		if (!path)
		{
			ms->state.exit_status = ERROR_BUILTIN;
			return ;
		}
	}
	if (chdir(path))
		ms->state.exit_status = ERROR_BUILTIN;
}
