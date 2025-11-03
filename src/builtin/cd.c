/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/03 14:38:24 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "io.h"

static int	get_prev_path(t_minishell *ms, t_node *node, char **path, bool is_first_cd);
static void	update_oldpwd(t_minishell *ms);
static int	get_home(t_minishell *ms, char **path);

int	cd(t_minishell *ms, t_node *node)
{
	char			*path;
	static bool		is_first_cd = true;

	path = node->cmd.args[1];
	if (!path)
	{
		if (get_home(ms, &path))
			return (ERROR_BUILTIN);
	}
	if (*path == '-')
	{
		if (get_prev_path(ms, node, &path, is_first_cd))
			return (ERROR_BUILTIN);
	}
	if (envll_findkey(&ms->state, "OLDPWD"))
		update_oldpwd(ms);
	if (chdir(path))
		warning(ms, str_join(ms, "cd: ", path, VOLATILE));
	is_first_cd = false;
	return (SUCCESS);
}

static int	get_prev_path(t_minishell *ms, t_node *node, char **path, bool is_first_cd)
{
	if (*(*path + 1) == '-')
	{
		if (get_home(ms, path))
			return (ERROR_BUILTIN);
		return (SUCCESS);
	}
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
	try_write_endl(ms, node->cmd.out, *path);
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

static int	get_home(t_minishell *ms, char **path)
{
		if (!envll_findkey(&ms->state, "HOME"))
		{
			warning(ms, "cd: HOME not set");
			return (ERROR_BUILTIN);
		}
		*path = envll_findkey(&ms->state, "HOME")->value;
		return (SUCCESS);
}
