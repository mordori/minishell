/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 22:27:08 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/12 16:02:56 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"
#include "arena.h"
#include "executor_utils.h"

void	close_node_fds(t_node *node)
{
	if (node->cmd.redir_in != STDIN_FILENO && node->cmd.redir_in != ERROR)
		close(node->cmd.redir_in);
	if (node->cmd.redir_out != STDOUT_FILENO && node->cmd.redir_out != ERROR)
		close(node->cmd.redir_out);
}

void	close_all_fds(t_minishell *ms)
{
	t_node	*node;

	node_scrollback(ms);
	node = ms->node;
	while (node)
	{
		close_node_fds(node);
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
