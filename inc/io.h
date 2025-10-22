/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 05:09:20 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/20 23:18:17 by myli-pen         ###   ########.fr       */
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
void	dup_io(t_node *node);
int		try_open(t_minishell *ms, char *file, int o_flag, int p_flag);
ssize_t	try_write(t_minishell *ms, int fd, char *src);
ssize_t	try_read(t_minishell *ms, int fd, char *buf, size_t n_bytes);

#endif
