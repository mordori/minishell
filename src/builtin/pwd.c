/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:03 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/23 21:47:25 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "io.h"

void	pwd(t_minishell *ms)
{
	char	*pwd;
	char	buf[PATH_MAX];

	pwd = getcwd(buf, sizeof(buf));
	if (!pwd)
	{
		ms->state.exit_status = ERROR_BUILTIN; //return errno or a bash-style/custom code?
		if (errno == ENOENT && ms->pwd[0])
		{
			try_write_endl(ms, ms->node->pipe_fds[1], ms->pwd);
			return ;
		}
		else
			error_exit(ms, "get cwd failed");
	}
	try_write_endl(ms, ms->node->pipe_fds[1], pwd);
}
