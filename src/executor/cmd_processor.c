/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:38:28 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/22 16:38:22 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "errors.h"

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

static inline char	*get_last_arg(t_minishell *ms, char **args)
{
	char	*result;
	t_env	*shell_v;

	while (*args)
	{
		result = *args;
		++args;
	}
	if (!ft_strcmp(result, "env"))
	{
		shell_v = envll_findkey(&ms->state, "SHELL");
		if (shell_v)
			result = str_join(ms, \
str_join(ms, shell_v->value, "/src/builtin/", VOLATILE), result, VOLATILE);
	}
	return (result);
}

void	update_env_lastcmd(t_minishell *ms, char **args)
{
	t_env	*lastcmd_v;

	copy_env_to(VOLATILE, ms);
	arena_reset(&ms->vars);
	lastcmd_v = envll_findkey(&ms->state, "_");
	if (lastcmd_v)
		replace_value(lastcmd_v, get_last_arg(ms, args));
	else
		var_to_node(ms, str_join(ms, "_=", get_last_arg(ms, args), VOLATILE), &ms->state.env);
	copy_env_to(PERSISTENT, ms);
	ms->state.envp = envll_to_envp(ms, ms->state.env);
}
