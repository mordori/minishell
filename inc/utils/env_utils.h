/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:29:00 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/03 17:48:33 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# include <stdlib.h>
# include "defines.h"
# include "arena_utils.h"

t_env	*ft_envnode_new(char *key, char *value);
void	ft_envadd_back(t_env **env_head, t_env *new_node);
char	*ft_keydup(char *key_src, char *key_end);

#endif
