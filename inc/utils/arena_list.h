/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:35:52 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/02 02:30:03 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ARENA_LIST_H
# define ARENA_LIST_H

# include "defines.h"
#include "libft_list.h"

t_list	*lstnew(t_minishell *ms, void *content);
bool	lstadd_back(t_list **lst, t_list *new);
int		lstsize(t_list *lst);

#endif
