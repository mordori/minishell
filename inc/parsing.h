/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:09:02 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/27 18:38:38 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <unistd.h>

# include "defines.h"

bool	parse_tokens(t_minishell *ms, t_token **tokens);
void	expand_variables(t_minishell *ms);
t_token	**create_tokens(char *src, t_minishell *ms);
bool	cmp_strs(const char **types, const char *src, const char **out);
bool	is_unclosed_quote(t_minishell *ms, const char **src);
bool	is_unsupported_char(t_minishell *ms, const char *src);
char	**tokenize(t_minishell *ms, char const *src);
void	add_src_len(char const **src, size_t *len);
void	march_quoted_word(char const **src, const char c, size_t *len);
bool	is_space(char c);
bool	is_operator(const char *src);
bool	is_redirection(const char *src);
bool	is_pipe(const char *src);
bool	is_unsupported_char(t_minishell *ms, const char *src);
void	expand_str(t_minishell *ms, char **src, t_expand_mode mode);

#endif
