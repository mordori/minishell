/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:58:00 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/05 17:32:13 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

void	node_scrollback(t_minishell *ms)
{
	while (ms->node && ms->node->prev)
		ms->node = ms->node->prev;
}

void	set_mode(t_minishell *ms)
{
	if (!ms->node->next)
		ms->state.mode = SIMPLE;
	else if (ms->node->next)
		ms->state.mode = PIPELINE;
}
