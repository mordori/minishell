/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:29:00 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/17 17:40:20 by myli-pen         ###   ########.fr       */
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
t_env	*ft_envnode_new(t_minishell *ms, char *key, char *value);
void	ft_envadd_back(t_env **env_head, t_env *new_node);
char	*ft_keydup(t_minishell *ms, char *key_src, char *key_end);
int		count_variables(t_env *env);
char	*join_keyvalue(char *key, char *value, char *dest);

//env_utils2.c
t_env	*envll_findkey(t_state *state, char *key);
bool	is_valid_key(const char *key, char *delimiter);
bool	replace_value(t_env *var, char *value);
t_env	*envlast(t_env *env);

#endif
