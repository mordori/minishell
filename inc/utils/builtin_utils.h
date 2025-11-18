/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:28:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/18 03:05:03 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_UTILS_H
# define BUILTIN_UTILS_H

# include "defines.h"
# include "builtin.h"

bool	is_pluschar(char *var, char delimiter);
bool	handle_cases(t_minishell *ms, int i, t_env *env, t_key_value *kv);
int		handle_cd_specs(\
t_minishell *ms, char **path, t_node *node, bool is_1st_cd);

#endif
