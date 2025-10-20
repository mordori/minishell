/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:26:59 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/20 01:19:00 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "cleanup.h"
#include "errors.h"

void	exitt(t_minishell *ms)
{
	int	bytes;
	int	status;

	bytes = write(1, "exit\n", 5);
	if (bytes == ERROR)
		error_exit(ms, "write failed");
	status = ms->state.exit_status;
	clean(ms);
	exit(status);
}

/*
 * NOTE:
"		DESCRIPTION
       The exit utility shall cause the shell to exit from its current  execu‐
       tion environment with the exit status specified by the unsigned decimal
       integer n.  If the current execution environment is a subshell environ‐
       ment, the shell shall exit from the subshell environment with the spec‐
       ified exit status and continue in the environment from which that  sub‐
       shell  environment was invoked; otherwise, the shell utility shall ter‐
       minate with the specified exit status. If n is specified, but its value
       is not between 0 and 255 inclusively, the exit status is undefined.
			A  trap  on  EXIT shall be executed before the shell terminates, except
       when the exit utility is invoked in that trap itself, in which case the
       shell shall exit immediately."
*/
