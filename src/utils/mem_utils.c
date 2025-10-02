/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:00:20 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/01 16:06:12 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem_utils.h"
#include "mem_arena.h"
#include "errors.h"

void	*alloc_system(t_minishell *ms, size_t size)
{
	void	*ptr;

	ptr = arena_alloc(&ms->system, size);
	if (!ptr)
		error_exit(ms, "System alloc failed");
	return (ptr);
}

void	*alloc_pool(t_minishell *ms, size_t size)
{
	void	*ptr;

	ptr = arena_alloc(&ms->pool, size);
	if (!ptr)
		error_exit(ms, "Pool alloc failed");
	return (ptr);
}
