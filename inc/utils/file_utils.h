/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 03:02:12 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/18 03:03:16 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_UTILS_H
# define FILE_UTILS_H

# define _GNU_SOURCE

# include <fcntl.h>
# include <unistd.h>

# include "defines.h"

int		try_open(t_minishell *ms, char *file, int o_flag, int p_flag);
ssize_t	try_write(t_minishell *ms, int fd, char *src);
ssize_t	try_write_endl(t_minishell *ms, int fd, char *src);
ssize_t	try_read(t_minishell *ms, int fd, char *buf, size_t n_bytes);

#endif
