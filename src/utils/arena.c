/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:05:05 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/02 21:11:07 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "libft_mem.h"

/**
 * @brief	Allocates and zero-initializes memory for the arena and initializes
 * its variables.
 *
 * @param	capacity Total bytes the arena can contain.
 *
 * @return	Created memory arena or NULL if creation fails.
 */
t_arena	arena_create(size_t capacity)
{
	t_arena	arena;

	arena.base = ft_calloc(sizeof(char), capacity);
	arena.capacity = capacity;
	arena.head = 0;
	return (arena);
}

/**
 * @brief	Reserves a block of memory from the arena and moves `head` index.
 *
 * @param	arena Pointer to the arena.
 * @param	size Amount of bytes to reserve from the arena.
 *
 * @return	Pointer to the block of memory that was reserved.
 */
void	*arena_alloc(t_arena *arena, size_t size)
{
	void	*ptr;

	if (arena->head + size > arena->capacity)
		return (NULL);
	ptr = arena->base + arena->head;
	arena->head += size;
	return (ptr);
}

/**
 * @brief	Resets the `head` index to the base of the arena and
 * zero-initializes the allocated memory.
 *
 * @note	Previously written memory will be overwritten by subsequent allocs.
 *
 * @param	arena Pointer to the arena.
 */
void	arena_reset(t_arena *arena)
{
	ft_memset(arena->base, 0, arena->capacity);
	arena->head = 0;
}

/**
 * @brief	Frees the memory allocated to the arena.
 *
 * @param	arena Pointer to the arena.
 */
void	arena_destroy(t_arena *arena)
{
	if (!arena)
		return ;
	if (arena->base)
		free(arena->base);
	arena->base = NULL;
}
