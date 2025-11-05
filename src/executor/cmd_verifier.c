/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_verifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:23:27 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/05 17:32:11 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "verifier_utils.h"

static int			verifier(t_minishell *ms, t_node *node);
static t_builtin	verify_builtin(char *cmd);
static char			*verify_extern(t_minishell *ms, char *cmd_name);

int	command_verification(t_minishell *ms, t_node *node)
{
	int		status;

	status = verifier(ms, node);
	if (status == ERROR_CMD_NOTFOUND)
	{
		errno = 0;
		warning(ms, str_join(\
ms, node->cmd.args[0], ": command not found", VOLATILE));
	}
	return (status);
}

static int	verifier(t_minishell *ms, t_node *node)
{
	t_cmd		*cmd;
	char		*cmd_name;

	if (node)
	{
		cmd = &node->cmd;
		if (cmd->args[0] == NULL)
			return (ERROR_CMD_NOTFOUND);
		cmd_name = cmd->args[0];
		cmd->builtin = verify_builtin(cmd_name);
		if (!cmd->builtin)
		{
			cmd->cmd = verify_extern(ms, cmd_name);
			if (!cmd->cmd)
				return (ERROR_CMD_NOTFOUND);
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

static char	*verify_extern(t_minishell *ms, char *cmd_name)
{
	char	*path;

	path = getenv("PATH");
	if (!path || cmd_name[0] == '/' || cmd_name[0] == '.')
		return (path_verif(cmd_name));
	return (environ_verif(ms, path, cmd_name));
}
