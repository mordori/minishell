/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:10:23 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/01 19:13:13 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_env	*partition(t_env *low, t_env *high);
static void	swap(t_env *a, t_env *b);

void	quicksort(t_env *low, t_env *high)
{
	t_env		*pivot;

	if (low != NULL && high != NULL && low != high && low != high->next)
	{
		pivot = partition(low, high);
		quicksort(low, pivot->prev);
		quicksort(pivot->next, high);
	}
}

static t_env	*partition(t_env *low, t_env *high)
{
	char		*pivot_val;
	t_env		*i;
	t_env		*current;

	pivot_val = high->key;
	i = low->prev;
	current = low;
	while (current != high)
	{
		if (ft_strcmp(current->key, pivot_val) <= 0)
		{
			if (i == NULL)
				i = low;
			else
				i = i->next;
			swap(i, current);
		}	
		current = current->next;
	}
	if (i == NULL)
		i = low;
	else
		i = i->next;
	swap(i, high);
	return (i);
}

static void	swap(t_env *a, t_env *b)
{
	const char		*temp_key;
	const char		*temp_val;

	temp_key = a->key;
	temp_val = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}
