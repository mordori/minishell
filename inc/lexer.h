/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 04:11:12 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/13 00:59:55 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "defines.h"

t_token	**create_tokens(char *src, t_minishell *ms);
bool	cmp_strs(const char **types, const char *src, const char **out);
bool	is_operator(const char *src);
bool	is_redirection(const char *src);
bool	is_pipe(const char *src);
bool	is_unclosed_quote(t_minishell *ms, const char **src);
bool	is_unsupported_char(t_minishell *ms, const char *src);
char	**str_split(t_minishell *ms, char const *src);
void	march_operator(char const **src, int *count);
void	add_src_len(char const **src, size_t *len);
void	march_quoted_word(char const **src, const char c, size_t *len);

#endif
