/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:05:32 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/06 05:55:35 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>

# include "defines.h"

void	*arena_alloc(t_arena *arena, size_t size);
t_arena	arena_create(t_minishell *ms, size_t capacity);
void	arena_destroy(t_arena *arena);
void	arena_reset(t_arena *arena);
void	*alloc_pool(t_minishell *ms, size_t size);
void	*alloc_system(t_minishell *ms, size_t size);

#endif
