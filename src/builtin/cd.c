/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/24 16:43:27 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "io.h"

static int	get_previous_path(t_minishell *ms, char **path, bool is_first_cd);
static void	update_oldpwd(t_minishell *ms);

int	cd(t_minishell *ms)
{
	char			*path;
	static bool		is_first_cd = true;

	path = ms->node->cmd.args[1];
	if (!path)
	{
		if (!envll_findkey(&ms->state, "HOME"))
		{
			warning(ms, "cd: HOME not set");
			return (ERROR_BUILTIN);
		}
		path = envll_findkey(&ms->state, "HOME")->value;
	}
	if (*path == '-')
	{
		if (get_previous_path(ms, &path, is_first_cd))
			return (ERROR_BUILTIN);
	}
	if (envll_findkey(&ms->state, "OLDPWD"))
		update_oldpwd(ms);
	if (chdir(path))
		warning(ms, str_join(ms, "cd: ", path, VOLATILE));
	is_first_cd = false;
	return (SUCCESS);
}

static int	get_previous_path(t_minishell *ms, char **path, bool is_first_cd)
{
	*path = NULL;
	if (is_first_cd)
		*path = getenv("OLDPWD");
	else
	{
		if (envll_findkey(&ms->state, "OLDPWD"))
			*path = envll_findkey(&ms->state, "OLDPWD")->value;
	}
	if (!*path)
	{
		warning(ms, "cd: OLDPWD not set");
		return (ERROR_BUILTIN);
	}
	try_write_endl(ms, ms->node->pipe_fds[1], *path);
	return (SUCCESS);
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
