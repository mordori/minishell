/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_syscall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:15:09 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/20 20:22:51 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "try_syscall.h"
#include "libft_str.h"
#include "errors.h"

int	try_write(t_minishell *ms, int fd, char *src)
{
	ssize_t	bytes;
	ssize_t	len;
	size_t	ulen;

	ulen = ft_strlen(src);
	if (ulen > LONG_MAX)
		error_exit(ms, "write src is longer than LONG_MAX");
	len = (ssize_t)ulen;
	bytes = write(fd, src, len);
	if (bytes != len)
		error_exit(ms, NULL);
	return (bytes);
}

int	try_open(t_minishell *ms, char *file, int o_flag, int p_flag)
{
	int	fd;

	fd = open(file, o_flag, p_flag);
	if (fd == ERROR)
		warning(ms, file);
	return (fd);
}

ssize_t	try_read(t_minishell *ms, int fd, char *buf, size_t n_bytes)
{
	ssize_t	bytes;

	bytes = read(fd, buf, n_bytes);
	if (bytes == ERROR)
		error_exit(ms, "read failed");
	return (bytes);
}
