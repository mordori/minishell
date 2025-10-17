/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:26:59 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/01 18:09:07 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	exitt(t_cmd *cmd, t_state *state)
{
	//FIX: remember to build this as soon as the exits and errors are clearer.
	//clean(ms);
	//exit(EXIT_SUCCESS);
	(void) cmd; (void) state;
	return ;
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
