/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_verification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:23:27 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/25 04:38:43 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static t_builtin	verify_builtin(char *cmd);
static char			*verify_path(t_minishell *ms, char *cmd_name);
static char			*env_path_verif(t_minishell *ms, char *path, char *cmd_name);
static char			*absolute_path_verif(t_minishell *ms, char *path);

int	command_verification(t_minishell *ms, t_node *node)
{
	t_cmd		*cmd;
	char		*cmd_name;

	if (node)
	{
		cmd = &node->cmd;
		cmd_name = cmd->args[0];
		cmd->builtin = verify_builtin(cmd_name);
		if (!cmd->builtin)
		{
			cmd->cmd = verify_path(ms, cmd_name);
			if (!cmd->cmd)
			{
				errno = 0;
				warning(ms, str_join(\
					ms, cmd->args[0], ": command not found", VOLATILE));
				return (ERROR_CMD_NOTFOUND);
			}
		}
		else
			cmd->cmd = cmd->args[0];
	}
	return (SUCCESS);
}

static t_builtin	verify_builtin(char *cmd)
{
	t_builtin	type;
	static char	*types[] = {\
		NULL, "echo", "cd", "pwd", "export", "unset", "env", "exit"};

	type = 1;
	while (type < 8)
	{
		if (ft_strcmp(types[type], cmd) == 0)
			return (type);
		type++;
	}
	return (FALSE);
}

static char	*verify_path(t_minishell *ms, char *cmd_name)
{
	char	*path;

	path = getenv("PATH");
	if (!path || cmd_name[0] == '/')
		return (absolute_path_verif(ms, cmd_name));
	return (env_path_verif(ms, path, cmd_name));
}

static char	*absolute_path_verif(t_minishell *ms, char *cmd_path)
{
	if (access(cmd_path, F_OK) == SUCCESS)
		return (cmd_path);
	(void)ms;
	//warning(ms, cmd_path);
	return (NULL);
}

static char	*env_path_verif(t_minishell *ms, char *path, char *cmd_name)
{
	char	**dir_list;
	char	*full_path;
	int		i;

	i = 0;
	dir_list = str_split(ms, path, ':');
	while (dir_list[i])
	{
		full_path = scan_directory(ms, dir_list[i], cmd_name);
		if (full_path)
			return (full_path);
		i++;
	}
	//warning(ms, cmd_name);
	return (NULL);
}
