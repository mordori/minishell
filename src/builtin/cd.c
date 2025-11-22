/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:45:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/22 15:45:20 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "file_utils.h"

static void	update_opwd(t_minishell *ms);
static void	update_pwd(t_minishell *ms);
static int	get_home(t_minishell *ms, char **path);

int	cd(t_minishell *ms, t_node *node)
{
	char			*path;
	static bool		is_1st_cd = true;

	if (node->cmd.args[1] && node->cmd.args[2])
	{
		errno = 0;
		warning(ms, str_join(ms, "cd: ", "too many arguments", VOLATILE));
		return (ERROR_GENERAL);
	}
	path = node->cmd.args[1];
	if (!path)
		if (get_home(ms, &path))
			return (ERROR_GENERAL);
	if (handle_cd_specs(ms, &path, is_1st_cd))
		return (ERROR_GENERAL);
	update_opwd(ms);
	is_1st_cd = false;
	if (chdir(path))
	{
		warning(ms, str_join(ms, "cd: ", path, VOLATILE));
		return (ERROR_GENERAL);
	}
	update_pwd(ms);
	return (SUCCESS);
}

int	get_opwd(t_minishell *ms, char **path, bool is_1st)
{
	if (*(*path + 1) == '-')
	{
		if (get_home(ms, path))
			return (ERROR_GENERAL);
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
		return (ERROR_GENERAL);
	}
	try_write_endl(ms, STDOUT_FILENO, *path);
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
	if (!pwd)
	{
		if (errno == ENOENT)
			warning(ms, "cd: error retrieving current directory: \
getcwd: cannot access parent directories");
		replace_value(pwdvar, str_join(ms, pwdvar->value, "/..", PERSISTENT));
	}
	else
		replace_value(pwdvar, str_dup(ms, pwd, PERSISTENT));
}

static int	get_home(t_minishell *ms, char **path)
{
	t_env		*home;

	home = envll_findkey(&ms->state, "HOME");
	if (!home || (home && !home->value[0]))
	{
		errno = 0;
		warning(ms, "cd: HOME not set");
		return (ERROR_GENERAL);
	}
	*path = home->value;
	return (SUCCESS);
}
