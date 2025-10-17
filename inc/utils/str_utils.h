/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:34:49 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/17 17:01:15 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_UTILS_H
# define STR_UTILS_H

# include "defines.h"

char	*str_dup(t_minishell *ms, const char *s);
char	*str_sub(\
t_minishell *ms, const char *src, unsigned int start, size_t len);
char	*str_join(t_minishell *ms, const char *s1, const char *s2);
char	**dup_envp_system(t_minishell *ms, char **envp);
char	*int_to_str(t_minishell *ms, int n);

#endif
