/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:38:28 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/04 13:44:33 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "errors.h"

void	run_node(t_minishell *ms, t_node *node)
{
	//FIXME: parent's custom signal handling back to default
	if (node->cmd.builtin)
	{
		if (exec_builtin(ms, node))
			error_exit(ms, NULL);
		clean(ms);
		exit(0);
	}
	else
	{
		if (exec_extern(ms, node))
			error_exit(ms, NULL);
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

	#ifdef DEBUG
	printf("execve has returned.\n");
	#endif

	ms->state.exit_status = errno;
	return (ERROR);
}

void	update_env_lastcmd(t_minishell *ms, char *cmd, t_builtin builtin)
{
	t_env	*shell_v;
	t_env	*lastcmd_v;

	copy_env_to(VOLATILE, ms);
	arena_reset(&ms->vars);
	if (builtin)
	{
		shell_v = envll_findkey(&ms->state, "SHELL");
		if (shell_v)
			cmd = str_join(ms, \
str_join(ms, shell_v->value, "/src/builtin/", VOLATILE), cmd, VOLATILE);
	}
	lastcmd_v = envll_findkey(&ms->state, "_");
	if (lastcmd_v)
		replace_value(lastcmd_v, cmd);
	else
		var_to_node(ms, str_join(ms, "_=", cmd, VOLATILE), &ms->state.env);
	copy_env_to(PERSISTENT, ms);
	ms->state.envp = envll_to_envp(ms, ms->state.env);
}
