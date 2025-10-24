/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:38:28 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/24 16:43:30 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "errors.h"

void	run_node(t_minishell *ms)
{
	//FIXME: parent's custom signal handling back to default
	if (ms->node->cmd.builtin)
		exec_builtin(ms);
	else
		exec_extern(ms);
	if (ms->state.exit_status)
		error_exit(ms, NULL);
}

int	exec_builtin(t_minishell *ms)
{
	static t_fun	*dt[8] = {NULL, &echo, &cd, &pwd, &expo, &unse, &env, &exi};

	return (dt[ms->node->cmd.builtin](ms));
}

int	exec_extern(t_minishell *ms)
{
	char	*command;
	char	**args;
	char	**envp;

	command = ms->node->cmd.cmd;
	args = ms->node->cmd.args;
	envp = ms->state.envp;
	execve(command, args, envp);
	ms->state.exit_status = errno;
	return (ERROR);
}
