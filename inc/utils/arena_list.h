/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:35:52 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/04 15:52:54 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_LIST_H
# define ARENA_LIST_H

# include "defines.h"
# include "libft_list.h"

t_list	*lstnew(t_minishell *ms, void *content);
bool	lstadd_back(t_list **lst, t_list *new);
size_t	lstsize(t_list *lst);

#endif
