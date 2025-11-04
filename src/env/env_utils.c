/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:24:14 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/04 12:39:13 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static size_t	keylen(char *key_src, char *key_end);

t_env	*ft_envnode_new(t_minishell *ms, char *key, char *valu, t_arena_type t)
{
	t_env	*node;

	node = NULL;
	if (t == PERSISTENT)
		node = alloc_vars(ms, sizeof(t_env));
	else if (t == VOLATILE)
		node = alloc_volatile(ms, sizeof(t_env));
	node->key = key;
	node->value = valu;
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

char	*ft_keydup(t_minishell *ms, char *key_src, char *key_end)
{
	size_t		len;
	size_t		i;
	char		*key;

	i = 0;
	len = keylen(key_src, key_end);
	key = alloc_vars(ms, (len + 1) * sizeof(char));
	while (i < len)
	{
		key[i] = key_src[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static size_t	keylen(char *key_src, char *key_end)
{
	size_t		len;

	len = 0;
	while (key_src[len])
	{
		if (key_end)
		{
			if (key_src[len] == *key_end)
			{
				if (key_src[len - 1] == '+')
					len--;
				return (len);
			}
		}
		len++;
	}
	return (len);
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
		dest[i] = value[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
