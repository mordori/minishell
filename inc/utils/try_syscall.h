/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_syscall.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:17:13 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/20 20:23:05 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRY_SYSCALL_H
# define TRY_SYSCALL_H

# include <unistd.h>
# include <fcntl.h>

# include "defines.h"

int		try_write(t_minishell *ms, int fd, char *src);
int		try_open(t_minishell *ms, char *file, int o_flag, int p_flag);
ssize_t	try_read(t_minishell *ms, int fd, char *buf, size_t n_bytes);

#endif
