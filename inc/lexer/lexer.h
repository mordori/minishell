/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 04:11:12 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/01 03:03:41 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "defines.h"

t_token	**create_tokens(char *src, t_minishell *ms);
bool	cmp_strs(const char **types, const char *src);
bool	is_operator(const char *src);
bool	is_quote(const char *src);

#endif
