/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:38:28 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/28 20:29:13 by myli-pen         ###   ########.fr       */
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
	ms->state.exit_status = errno;
	return (ERROR);
}
