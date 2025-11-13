/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_verifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:23:27 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/13 10:44:12 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "verifier_utils.h"

static int			verifier(t_minishell *ms, t_node *node);
static t_builtin	verify_builtin(char *cmd);
static char			*verify_extern(t_minishell *ms, char *cmd_name);

int	command_verification(t_minishell *ms, t_node *node)
{
	char			*arg;
	int				status;
	struct stat		buf;

	status = verifier(ms, node);
	arg = node->cmd.args[0];
	if (status == ERROR_CMD_NOTFOUND)
	{
		errno = 0;
		warning(ms, str_join(ms, arg, ": command not found", VOLATILE));
	}
	if (status == ERROR_CMD_CANTEXEC)
	{
		warning(ms, arg);
	}
	stat(node->cmd.cmd, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		warning(ms, str_join(ms, arg, ": Is a directory", VOLATILE));
		status = ERROR_CMD_CANTEXEC;
	}
	return (status);
}

static int	verifier(t_minishell *ms, t_node *node)
{
	t_cmd	*cmd;
	char	*cmd_name;

	if (node)
	{
		cmd = &node->cmd;
		if (cmd->args == NULL)
			return (ERROR_CMD_NOTFOUND);
		cmd_name = cmd->args[0];
		cmd->builtin = verify_builtin(cmd_name);
		if (!cmd->builtin)
		{
			cmd->cmd = verify_extern(ms, cmd_name);
			if (!cmd->cmd)
				return (ERROR_CMD_NOTFOUND);
			if (access(cmd->cmd, X_OK) == -1)
				return (ERROR_CMD_CANTEXEC);
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
	t_env	*path_env;

	path_env = envll_findkey(&ms->state, "PATH");
	if (!path_env || cmd_name[0] == '/' || cmd_name[0] == '.')
	{
		return (path_verif(cmd_name));
	}
	return (environ_verif(ms, path_env->value, cmd_name));
}
