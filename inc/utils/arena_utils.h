/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:27:28 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/02 01:29:39 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_UTILS_H
# define ARENA_UTILS_H

# include "defines.h"

void	*alloc_pool(t_minishell *ms, size_t size);
void	*alloc_system(t_minishell *ms, size_t size);

#endif
