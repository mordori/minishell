/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:03 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/15 17:34:33 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	pwd(t_cmd *cmd, t_state *shell_state)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		shell_state->exit_status = ERROR_BUILTIN; //return errno or a bash-style/custom code?
		return ;
	}
	ft_printf("%s\n", pwd);
	free(pwd);
}
