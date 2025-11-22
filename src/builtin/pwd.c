/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:03 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/22 15:36:39 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	pwd(t_minishell *ms, t_node *node)
{
	char	*pwd;
	char	buf[PATH_MAX];

	(void)node;
	pwd = getcwd(buf, sizeof(buf));
	if (!pwd)
	{
		ms->state.exit_status = ERROR_GENERAL;
		if (errno == ENOENT && ms->pwd[0])
		{
			try_write_endl(ms, STDOUT_FILENO, ms->pwd);
			return (SUCCESS);
		}
		else
			error_exit(ms, "getcwd failed");
	}
	try_write_endl(ms, STDOUT_FILENO, pwd);
	return (SUCCESS);
}
