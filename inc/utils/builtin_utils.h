/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:28:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/22 15:45:04 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_UTILS_H
# define BUILTIN_UTILS_H

# include "defines.h"
# include "builtin.h"

bool	is_pluschar(char *var, char delimiter);
bool	handle_cases(t_minishell *ms, int i, t_env *env, t_key_value *kv);
int		handle_cd_specs(t_minishell *ms, char **path, bool is_1st_cd);

#endif
