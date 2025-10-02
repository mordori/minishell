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

static int	partition(char **envp, int low, int high);
static void	swap(char **a, char **b);
static int	ft_strcmp(const char *s1, const char *s2);

void	quicksort(char **envp, int low, int high)
{
	size_t		i;
	size_t		pivot;

	i = 0;
	pivot = partition(envp, low, high);
	if (len <= 1)
		return ;
	while (i < len)
	{
		if (ft_strcmp(envp[i], envp[len - 1]) < 0)
			swap(envp + i, envp + pivot++);
		i++;
	}
}

static int	partition(char **envp, int low, int high)
{
//FIXME: keep going based on GeeksForGeeks guide!!!!!!	
	//BUT IT MIGHT HAVE TO BE ADAPTED FOR LINKED LIST.
	//OR THEN, parse envp for printing purposes after quicksort. (maybe easier)
}

static void	swap(char **a, char **b)
{
	const char		*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t		i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}
