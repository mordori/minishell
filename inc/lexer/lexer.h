/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 04:11:12 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/01 01:19:01 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "defines.h"

t_token	**create_tokens(char *src, t_minishell *ms);
bool	cmp_type(const char **types, const char *src);
bool	cmp_types(const char *src);

#endif
