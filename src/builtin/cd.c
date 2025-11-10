/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/10 17:58:43 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "io.h"

static int	get_opwd(t_minishell *ms, t_node *node, char **path, bool is_1st);
static void	update_opwd(t_minishell *ms);
static void	update_pwd(t_minishell *ms);
static int	get_home(t_minishell *ms, char **path);

int	cd(t_minishell *ms, t_node *node)
{
	char			*path;
	static bool		is_1st_cd = true;

	if (node->cmd.args[2])
	{
		warning(ms, str_join(ms, "cd: ", "too many arguments", VOLATILE));
		return (ERROR_GENERAL);
	}
	path = node->cmd.args[1];
	if (!path)
	{
		if (get_home(ms, &path))
			return (ERROR_BUILTIN);
	}
	if (*path == '-')
	{
		if (get_opwd(ms, node, &path, is_1st_cd))
			return (ERROR_BUILTIN);
	}
	update_opwd(ms);
	if (chdir(path))
		warning(ms, str_join(ms, "cd: ", path, VOLATILE));
	else
		update_pwd(ms);
	is_1st_cd = false;
	return (SUCCESS);
}

static int	get_opwd(t_minishell *ms, t_node *node, char **path, bool is_1st)
{
	if (*(*path + 1) == '-')
	{
		if (get_home(ms, path))
			return (ERROR_BUILTIN);
		return (SUCCESS);
	}
	*path = NULL;
	if (is_1st)
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

static void	update_opwd(t_minishell *ms)
{
	t_env		*oldpwd;
	char		*current_pwd;
	char		buf[PATH_MAX];

	current_pwd = getcwd(buf, sizeof(buf));
	oldpwd = envll_findkey(&ms->state, "OLDPWD");
	if (oldpwd)
		replace_value(oldpwd, str_dup(ms, current_pwd, PERSISTENT));
}

static void	update_pwd(t_minishell *ms)
{
	t_env		*pwdvar;
	char		*pwd;
	char		buf[PATH_MAX];

	pwd = getcwd(buf, sizeof(buf));
	pwdvar = envll_findkey(&ms->state, "PWD");
	if (pwdvar)
		replace_value(pwdvar, str_dup(ms, pwd, PERSISTENT));
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
