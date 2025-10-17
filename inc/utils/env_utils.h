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
# include "arena.h"
# include "libft_str.h"
# include "libft_utils.h"

//env_utils.c
t_env	*ft_envnode_new(char *key, char *value);
void	ft_envadd_back(t_env **env_head, t_env *new_node);
char	*ft_keydup(char *key_src, char *key_end);
int		count_variables(t_env *env);
char	*join_keyvalue(char *key, char *value, char *dest);

//env_utils2.c
t_env	**envll_findkey(t_state *state, char *key);
bool	is_valid_key(const char *key, char *delimiter);
static bool	is_valid_identifier(const char c);
bool	replace_value(t_env **var, char *value);

#endif
