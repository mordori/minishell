/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 02:48:12 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/18 03:01:59 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_utils.h"
#include "libft_str.h"
#include "errors.h"

ssize_t	try_write(t_minishell *ms, int fd, char *src)
{
	ssize_t	bytes;
	ssize_t	len;
	size_t	ulen;

	ulen = ft_strlen(src);
	if (ulen > SSIZE_MAX)
		error_exit(ms, "write src is longer than SSIZE_MAX");
	len = (ssize_t)ulen;
	bytes = write(fd, src, len);
	if (bytes != len)
	{
		close(fd);
		error_exit(ms, "write failed");
	}
	return (bytes);
}

ssize_t	try_write_endl(t_minishell *ms, int fd, char *src)
{
	ssize_t	bytes;

	bytes = try_write(ms, fd, src);
	bytes += try_write(ms, fd, "\n");
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
	{
		close(fd);
		error_exit(ms, "read failed");
	}
	return (bytes);
}
