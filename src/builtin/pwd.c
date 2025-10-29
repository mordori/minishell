/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:03 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/24 16:43:19 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "io.h"

int	pwd(t_minishell *ms, t_node *node)
{
	char	*pwd;
	char	buf[PATH_MAX];

	pwd = getcwd(buf, sizeof(buf));
	if (!pwd)
	{
		ms->state.exit_status = ERROR_BUILTIN;
		if (errno == ENOENT && ms->pwd[0])
		{
			try_write_endl(ms, node->pipe_fds[1], ms->pwd);
			return (SUCCESS);
		}
		else
			error_exit(ms, "get cwd failed");
	}
	try_write_endl(ms, node->pipe_fds[1], pwd);
	return (SUCCESS);
}
