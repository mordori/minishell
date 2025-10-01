/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_arena.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:05:32 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/29 04:09:03 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_ARENA_H
# define MEM_ARENA_H

# include <stdlib.h>

# include "defines.h"

void		*arena_alloc(t_mem_arena *arena, size_t size);
t_mem_arena	arena_create(size_t capacity);
void		arena_destroy(t_mem_arena *arena);
void		arena_reset(t_mem_arena *arena);

#endif
