/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_arena.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:05:32 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/21 01:56:01 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_ARENA_H
# define MEM_ARENA_H

# include <stdlib.h>

# include "defines.h"

t_mem_arena	arena_create(size_t capacity);
void		*arena_alloc(t_mem_arena *arena, size_t size);
void		arena_reset(t_mem_arena *arena);
void		arena_destroy(t_mem_arena *arena);

#endif
