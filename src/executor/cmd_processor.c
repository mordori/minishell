/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:38:28 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/23 16:14:58 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "errors.h"

void	run_node(t_minishell *ms)
{
	//FIXME: parent's custom signal handling back to default
	printf("Cmd: %s is in run_node phase.\n", ms->node->cmd.cmd);
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
	char	*command;
	char	**args;
	char	**envp;

	printf("Cmd: %s is in exec_extern phase.\n", ms->node->cmd.cmd);
	command = ms->node->cmd.cmd;
	args = ms->node->cmd.args;
	envp = ms->state.envp;
	execve(command, args, envp); //execve should automatically clean up all memory, even heap
	//if (errno) //return to run_node if execve failed
	//	warning(ms, command);
	return ;
}
