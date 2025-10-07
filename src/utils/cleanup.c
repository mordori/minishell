/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 22:27:08 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/07 16:46:28 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"
#include "arena.h"

void	close_fds(t_minishell *ms)
{
	while (ms->node)
	{
		if (ms->node->cmd.in > STDOUT_FILENO)
			close(ms->node->cmd.in);
		if (ms->node->cmd.out > STDOUT_FILENO)
			close(ms->node->cmd.out);
		ms->node = ms->node->next;
	}
}

/**
 * @brief	Destroys created memory arenas from minishell.
 */
void	clean(t_minishell *ms)
{
	if (!ms)
		return ;
	close_fds(ms);
	arena_destroy(&ms->pool);
	arena_destroy(&ms->system);
	rl_clear_history();
	// if (ms->line)
	// 	free(ms->line);
	ms->line = NULL;
}
