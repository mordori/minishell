/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:03 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/17 17:26:40 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	pwd(t_minishell *ms)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ms->state.exit_status = ERROR_BUILTIN; //return errno or a bash-style/custom code?
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
}
