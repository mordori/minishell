/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:27:29 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/06 08:13:29 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "arena_list.h"
#include "arena.h"
#include "libft_list.h"

t_list	*lstnew(t_minishell *ms, void *content)
{
	t_list	*new;

	new = alloc_pool(ms, sizeof(*new));
	new->content = content;
	new->next = NULL;
	return (new);
}

bool	lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst)
		return (false);
	if (!*lst)
	{
		*lst = new;
		return (true);
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (true);
}

int	lstsize(t_list *lst)
{
	int	len;

	if (!lst)
		return (false);
	len = 0;
	while (lst)
	{
		++len;
		lst = lst->next;
	}
	return (len);
}

