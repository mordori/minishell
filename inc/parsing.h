/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:39:17 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/07 14:39:20 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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
bool	expand_str(t_minishell *ms, char **src, t_expand_mode mode);
char	*remove_quotes(t_minishell *ms, char *src);
void	split_words(t_minishell *ms, char *src, t_list **list);
void	join_var_name(\
t_minishell *ms, char **str, char **result, t_expand_mode mode);
void	join_var(\
t_minishell *ms, char **str, char **result, char quote, t_expand_mode mode);
char	*find_quote(char *str);

#endif
