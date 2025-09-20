/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:05:05 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/21 01:55:11 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem_arena.h"

t_mem_arena	arena_create(size_t capacity)
{
	t_mem_arena	arena;

	arena.tail = malloc(capacity);
	arena.capacity = capacity;
	arena.head = 0;
	return (arena);
}

void	*arena_alloc(t_mem_arena *arena, size_t size)
{
	void	*ptr;

	if (arena->head + size > arena->capacity)
		return (NULL);
	ptr = arena->tail + arena->head;
	arena->head += size;
	return (ptr);
}

void	arena_reset(t_mem_arena *arena)
{
	arena->head = 0;
}

void	arena_destroy(t_mem_arena *arena)
{
	free(arena->tail);
}
