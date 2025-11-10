/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:28:09 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/04 12:06:29 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_UTILS_H
# define BUILTIN_UTILS_H

# include "builtin.h"

bool	is_pluschar(char *var, char delimiter);
bool	handle_cases(t_minishell *ms, int i, t_env *env, t_key_value *kv);

#endif
