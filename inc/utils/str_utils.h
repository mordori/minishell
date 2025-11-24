/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:34:49 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/22 19:07:14 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_UTILS_H
# define STR_UTILS_H

# include "defines.h"

char	*str_dup(t_minishell *ms, const char *s, t_arena_type type);
char	*str_sub(\
t_minishell *ms, t_arena_type type, const char *src, size_t len);
char	*str_join(\
t_minishell *ms, const char *s1, const char *s2, t_arena_type type);
char	*uint_to_str(t_minishell *ms, unsigned int n);
char	**str_split(t_minishell *ms, char const *s, char c);
bool	is_whitespace(const char *src, const char *ifs);
char	*str_trim(char *src, const char *set);
size_t	int_to_str(int n, char *buf);

#endif
