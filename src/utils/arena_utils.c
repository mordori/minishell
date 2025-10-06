/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:00:20 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/06 17:26:42 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "errors.h"

void	*alloc_system(t_minishell *ms, size_t size)
{
	void	*ptr;

	ptr = arena_alloc(&ms->system, size);
	if (!ptr)
		warning_system(ms);
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
