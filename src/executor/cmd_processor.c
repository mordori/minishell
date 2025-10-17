/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:38:28 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/17 17:46:11 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	run_node(t_minishell *ms)
{
	//FIXME: parent's custom signal handling back to default
	if (ms->node->cmd.builtin)
		exec_builtin(ms);
	else
		exec_extern(ms);
	//clean_exit();  // FIXME: for builtins: free everything? Even FDs need to be closed according to many ppl.
}

void	exec_builtin(t_minishell *ms)
{
	static t_fun	*dt[8] = {NULL, &echo, &cd, &pwd, &export, &unset, &env, &exitt};

	dt[ms->node->cmd.builtin](ms);
}

void	exec_extern(t_minishell *ms)
{
	char		*command;
	char		**args;
	char		**envp;

	command = ms->node->cmd.cmd;
	args = ms->node->cmd.args + 1;
	envp = ms->state.envp;
	execve(command, args, envp); //execve should automatically clean up all memory, even heap
	if (errno) //return to run_node if execve failed
		//FIX: handle error.
		return ;
}
