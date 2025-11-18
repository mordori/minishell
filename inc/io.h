/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 05:09:20 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/18 03:03:07 by myli-pen         ###   ########.fr       */
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

void	setup_io(t_minishell *ms, t_node *node);
void	dup_redirections(t_minishell *ms, t_node *node);

#endif
