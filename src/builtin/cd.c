/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/23 21:07:48 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "io.h"

static void	get_previous_path(t_minishell *ms, char **path, bool is_first_cd);
static void	update_oldpwd(t_minishell *ms);

void	cd(t_minishell *ms)
{
	char		*path;
	static bool	is_first_cd = true;

	path = ms->node->cmd.args[1];
	if (!path)
	{
		path = getenv("HOME");
		if (!path)
		{
			ms->state.exit_status = ERROR_BUILTIN;
			return ;
		}
	}
	if (*path == '-')
		get_previous_path(ms, &path, is_first_cd);
	update_oldpwd(ms);
	if (chdir(path))
		ms->state.exit_status = ERROR_BUILTIN;
	is_first_cd = false;
}

static void	get_previous_path(t_minishell *ms, char **path, bool is_first_cd)
{
	if (is_first_cd)
		*path = getenv("OLDPWD");
	else
		*path = envll_findkey(&ms->state, "OLDPWD")->value;
	try_write_endl(ms, ms->node->pipe_fds[1], *path);
}

static void	update_oldpwd(t_minishell *ms)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	replace_value(\
		envll_findkey(&ms->state, "OLDPWD"), \
		str_dup(ms, current_pwd, PERSISTENT));
	free(current_pwd);
}
