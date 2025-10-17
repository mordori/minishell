/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:09:02 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/16 05:10:21 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <unistd.h>

# include "defines.h"

bool	parse_tokens(t_minishell *ms, t_token **tokens);
void	expand_variables(t_minishell *ms);

#endif
