/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:38:28 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/23 01:03:53 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "errors.h"
#include "main.h"

void	run_node(t_minishell *ms, t_node *node)
{
	if (node->cmd.builtin)
	{
		ms->state.exit_status = exec_builtin(ms, node);
		if (ms->state.exit_status)
			error_exit(ms, "Builtin exit");
		clean(ms);
		exit(0);
	}
	else
	{
		if (exec_extern(ms, node))
			error_exit(ms, "External exit");
	}
}

int	exec_builtin(t_minishell *ms, t_node *node)
{
	static t_fun	*dt[8] = {NULL, &echo, &cd, &pwd, &expo, &unse, &env, &exi};

	return (dt[node->cmd.builtin](ms, node));
}

int	exec_extern(t_minishell *ms, t_node *node)
{
	char	*command;
	char	**args;
	char	**envp;

	command = node->cmd.cmd;
	args = node->cmd.args;
	envp = ms->state.envp;
	execve(command, args, envp);
	return (ERROR);
}

static inline char	*get_last_arg(char **args)
{
	char	*result;

	result = NULL;
	while (*args)
	{
		result = *args;
		++args;
	}
	return (result);
}

void	set_env_defaults(t_minishell *ms, char **args)
{
	t_env		*lastcmd_v;
	static char	*init_args[] = {"minishell initialization", NULL};

	if (!args)
		args = init_args;
	copy_env_to(VOLATILE, ms);
	arena_reset(&ms->vars);
	lastcmd_v = envll_findkey(&ms->state, "_");
	if (lastcmd_v)
		replace_value(lastcmd_v, get_last_arg(args));
	else
		var_to_node(\
ms, str_join(ms, "_=", get_last_arg(args), VOLATILE), &ms->state.env);
	if (!envll_findkey(&ms->state, "PWD"))
	{
		store_pwd(ms);
		var_to_node(\
ms, str_join(ms, "PWD=", ms->pwd, VOLATILE), &ms->state.env);
	}
	if (!envll_findkey(&ms->state, "SHLVL"))
		var_to_node(ms, str_join(ms, "SHLVL=", "0", VOLATILE), &ms->state.env);
	copy_env_to(PERSISTENT, ms);
	ms->state.envp = envll_to_envp(ms, ms->state.env);
}
