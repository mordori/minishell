/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:58:00 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/16 16:00:09 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "executor.h"

bool	is_builtin(t_cmd *command) //the parameter/member format depends on parser output
{
	return (command->cmd == ECHO
		|| command->cmd == CD
		|| command->cmd == PWD
		|| command->cmd == EXPORT
		|| command->cmd == UNSET
		|| command->cmd == ENV
		|| command->cmd == EXIT);
}

/* 
 	* fork_child() takes a pointer to a child_pid, and modifies it with the new process ID
 	* it does basic error checking for fork() which returns -1 if forking failed
 	* the functio itself returns just 0 if forking succeeded.
 	* The return values can trigger further error handlin in caller,
 	* but its caller's responsibility to actually diverge 
 	* the child process from the parent process using the child_pid,
	* as the parent will see child_pid as some positive numba like 1,
	* while the child will see child_pid as 0.
*/
int	fork_child(pid_t *child_pid, t_state *shell);
{
	*child_pid = fork();
	if (*child_pid == -1)
	{
		shell->exit_status = ERROR_FORKING;
		return (ERROR_FORKING);
	}
	return (SUCCESS);
}
