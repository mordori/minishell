/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:00:20 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/17 17:36:28 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "errors.h"

void	*alloc_vars(t_minishell *ms, size_t size)
{
	return (alloc_persistent(ms, &ms->vars, size));
}

void	*alloc_persistent(t_minishell *ms, t_arena *arena, size_t size)
{
	void	*ptr;

	if (arena->type != PERSISTENT)
		error_exit(ms, "trying to allocate persistent memory to a volatile arena");
	ptr = arena_alloc(arena, size);
	if (!ptr)
		warning(ms, "persistent arena is at capacity: memory was not allocated\n");
	return (ptr);
}

void	*alloc_volatile(t_minishell *ms, size_t size)
{
	void	*ptr;

	ptr = arena_alloc(&ms->pool, size);
	if (!ptr)
		error_exit(ms, "volatile memory arena depleted");
	return (ptr);
}
