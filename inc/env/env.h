/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:17:25 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/04 12:39:22 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include <unistd.h>
# include "arena.h"
# include "defines.h"
# include "libft_str.h"
# include "libft_utils.h"
# include "str_utils.h"

//env_handler.c
int		envp_to_envll(t_minishell *ms, char **envp);
void	var_to_node(t_minishell *ms, char *var, t_env **env);
char	**envll_to_envp(t_minishell *ms, t_env *env);
char	*get_env_val(t_minishell *ms, char *key);

//quicksort.c
void	quicksort(t_env *low, t_env *high);

//env_utils.c
t_env	*ft_envnode_new(t_minishell *ms, char *key, char *valu, t_arena_type t);
void	ft_envadd_back(t_env **env_head, t_env *new_node);
char	*ft_keydup(t_minishell *ms, char *key_src, char *key_end);
char	*join_keyvalue(char *key, char *value, char *dest);

//env_utils2.c
t_env	*envll_findkey(t_state *state, char *key);
bool	is_valid_key(const char *key, char *delimiter);
bool	replace_value(t_env *var, char *value);
t_env	*envlast(t_env *env);
int		count_variables(t_env *env);

//mem_transfer.c
void	copy_env_to(t_arena_type to_type, t_minishell *ms);

#endif
