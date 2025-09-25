/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:41:25 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/25 14:30:26 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	run_node(t_node *node, t_state *shell) //t_state contained in T_MINISHELL, if wholistic mem management adopted.
{
	//parent's custom signal handling set back to default
	exec_extern(cmd, shell);
	//if (ms->state->exit_status)		IF WE AVOID WRITES INTO MEMORY ENTIRELY, MAYBE NO NEED TO CLEAN IN CHILD (except if parent wrote in meantime)
	//	error_exit();
}
