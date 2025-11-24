/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:03 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/23 22:08:12 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	pwd(t_minishell *ms, t_node *node)
{
	char	*pwd;
	char	buf[PATH_MAX];
	int		fd_out;

	fd_out = STDOUT_FILENO;
	if (ms->state.mode == SIMPLE)
		fd_out = node->cmd.redir_out;
	pwd = getcwd(buf, sizeof(buf));
	if (!pwd)
	{
		ms->state.exit_status = ERROR_GENERAL;
		if (errno == ENOENT && ms->pwd[0])
		{
			try_write_endl(ms, fd_out, ms->pwd);
			return (SUCCESS);
		}
		else
			error_exit(ms, "getcwd failed");
	}
	try_write_endl(ms, fd_out, pwd);
	return (SUCCESS);
}
