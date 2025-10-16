/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 05:09:20 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/16 05:31:28 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# define _GNU_SOURCE

# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "defines.h"

void	setup_io(t_minishell *ms);
void	dup_io(t_node *node);
void	write_heredoc(t_minishell *ms, t_node *node, char *eof);

#endif
