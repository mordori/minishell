/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_verification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:23:27 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/14 15:57:57 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//FIXME: to do: ft_strjoin and ft_split called in scan_directory are not memarena-friendly rn.

void	command_verification(t_minishell *ms)
{
	t_node		*node;
	t_cmd		*cmd;
	char		*cmd_name;

	node = ms->node;
	if (node)
	{
		cmd = node->cmd;
		cmd_name = cmd->args[0];
		cmd->builtin = verify_builtin(cmd_name);
		if (!cmd->buitin)
		{
			cmd->cmd = verify_path(cmd_name);
			if (!cmd->cmd)
			{
				ms->state->exit_status = ERROR;
				return ;
			}
		}
		else
			cmd->cmd = cmd->args[0];
		node = node->next;
	}
}

t_builtin	verify_builtin(char *cmd)
{
	t_builtin	type;
	char		**types;

	type = 1;
	types = {NULL, "echo", "cd", "pwd", "export", "unset", "env", "exit"};
	while (type < 8)
	{
		if (ft_strcmp(types[type], cmd) == 0)
			return (type);
		type++;
	}
	return (FALSE);
}

char	*verify_path(char *cmd_name)
{
	char	*path;
	int		i;

	i = 0;
	path = getenv("PATH");
	if (!path || cmd_name[0] == '/')
		return (absolute_path_verif(cmd_name));
	return (env_path_verif(path, cmd_name));
}

char	*env_path_verif(char *path, char *cmd_name)
{
	char			**dir_list;
	char			*full_path;
	int				i;

	i = 0;
	dir_list = ft_split(path, ':'); //FIXME: ft_split malloccaa
	while (dir_list[i])
	{
		full_path = scan_directory(dir_list[i]);
		if (full_path)
			return (full_path);
		i++;
	}
	printf("%s: command not found", cmd_name);
	return (NULL);
}

char	*absolute_path_verif(char *path)
{
	if (access(path, F_OK) == SUCCESS)
		return (path);
	printf("minishell: %s: No such file or directory", path);
	return (NULL);
}
