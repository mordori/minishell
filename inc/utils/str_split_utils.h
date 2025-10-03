/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 01:11:45 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/03 01:12:54 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_SPLIT_UTILS_H
# define STR_SPLIT_UTILS_H

# include "defines.h"

void	march_operator(char const **src, int *count);
void	is_quote_closed(t_minishell *ms, char const **src, char c, int *count);
void	add_src_len(char const **src, size_t *len);
void	march_quote(char const **src, const char c, size_t *len);

#endif
