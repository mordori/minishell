/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:09:02 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/02 19:39:35 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "defines.h"

t_command	*parse_tokens(t_minishell *ms, t_token **tokens);
void		expand_variables(t_command **cmd);
void		handle_redirections(t_command **cmd);

#endif
