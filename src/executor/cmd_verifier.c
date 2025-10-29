/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_verifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:23:27 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/28 00:05:38 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "verifier_utils.h"

static t_builtin	verify_builtin(char *cmd);
static char			*verify_extern(t_minishell *ms, char *cmd_name);
//static void			update_lastarg_var(t_minishell *ms, char *last_arg);

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
			cmd->cmd = verify_extern(ms, cmd_name);
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
		//update_lastarg_var(ms, cmd->cmd);
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

/*
static void	update_lastarg_var(t_minishell *ms, char *last_arg)
{
	t_env	*lastarg_var;

	copy_env_to(VOLATILE, ms);
	arena_reset(&ms->vars);
	lastarg_var = envll_findkey(&ms->state, "_");
	replace_value(lastarg_var, last_arg);
	copy_env_to(PERSISTENT, ms);
}
*/