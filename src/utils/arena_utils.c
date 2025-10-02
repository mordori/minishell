/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:00:20 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/02 21:10:34 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_utils.h"
#include "arena.h"
#include "errors.h"

void	*alloc_system(t_minishell *ms, size_t size)
{
	void	*ptr;

	ptr = arena_alloc(&ms->system, size);
	if (!ptr)
		error_exit(ms, "system memory depleted");
	return (ptr);
}

void	*alloc_pool(t_minishell *ms, size_t size)
{
	void	*ptr;

	ptr = arena_alloc(&ms->pool, size);
	if (!ptr)
		error_exit(ms, "pool memory depleted");
	return (ptr);
}
