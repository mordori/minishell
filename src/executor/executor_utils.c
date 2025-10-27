/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:58:00 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/27 12:41:40 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

void	check_fds(int *fds)
{
	(void) fds;
	//struct stat	buffer;
	//int			i;

	//fstat(fd[i], &buffer); for checking if FDs are open or closed
}

void	node_scrollback(t_minishell *ms)
{
	while (ms->node->prev)
		ms->node = ms->node->prev;
}

void	set_mode(t_minishell *ms)
{
	if (!ms->node->next)
		ms->state.mode = SIMPLE;
	else if (ms->node->next)
		ms->state.mode = PIPELINE;
}
