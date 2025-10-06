/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:24:14 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/02 16:51:14 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_utils.h"

t_env	*ft_envnode_new(char *key, char *value)
{
	t_env			*node;

	node = alloc_pool(sizeof(t_env));
	node->key = content;
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_envadd_back(t_env **env_head, t_env *new_node)
{
	t_env	*last;

	if (*env_head == NULL)
		*env_head = new_node;
	else
	{
		last = *env_head;
		while (last->next)
			last = last->next;
		last->next = new_node;
		new_node->prev = last;
	}
}

char	*ft_keydup(char *key_src, char *key_end)
{
	size_t		len;
	size_t		i;
	char		*key;

	i = 0;
	len = 0;
	if (!key_end)
		return (key_src);
	while (key_src[len] != *key_end)
		len++;
	key = alloc_pool((len + 1) * sizeof(char));
	while (i < len)
	{
		key[i] = key_src[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

int	count_variables(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*join_keyvalue(char *key, char *value, char *dest)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (key[i])
	{
		dest[i] = key[i];
		i++;
	}
	dest[i++] = '=';
	while (value[j])
	{
		dest[i]	= value[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
