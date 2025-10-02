/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:05:32 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/02 01:29:12 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>

# include "defines.h"

void	*arena_alloc(t_arena *arena, size_t size);
t_arena	arena_create(size_t capacity);
void	arena_destroy(t_arena *arena);
void	arena_reset(t_arena *arena);

#endif
