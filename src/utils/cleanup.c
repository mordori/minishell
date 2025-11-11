/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 22:27:08 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/03 16:24:41 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"
#include "arena.h"
#include "executor_utils.h"

void	close_fds(t_node *node)
{
	if (node->cmd.in != STDIN_FILENO && node->cmd.in != ERROR)
		close(node->cmd.in);
	if (node->cmd.out != STDOUT_FILENO && node->cmd.out != ERROR)
		close(node->cmd.out);
}

void	close_all_fds(t_minishell *ms)
{
	t_node	*node;

	node_scrollback(ms);
	node = ms->node;
	while (node)
	{
		close_fds(node);
		node = node->next;
	}
}

/**
 * @brief	Destroys created memory arenas from minishell.
 */
void	clean(t_minishell *ms)
{
	if (!ms)
		return ;
	close_all_fds(ms);
	arena_destroy(&ms->pool);
	arena_destroy(&ms->vars);
	rl_clear_history();
}
