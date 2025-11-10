/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 05:06:20 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/07 17:26:43 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "libft_str.h"
#include "errors.h"

void	dup_io(t_node *node)
{
	if (node->cmd.in != STDIN_FILENO)
	{

	#ifdef DEBUG
	#include <stdio.h>
	printf("cmd in: %d\n", node->cmd.in);
	#endif

		dup2(node->cmd.in, STDIN_FILENO);
		close (node->cmd.in);
	}
	if (node->cmd.out != STDOUT_FILENO)
	{

	#ifdef DEBUG
	#include <stdio.h>
	printf("cmd out: %d\n", node->cmd.out);
	#endif

		dup2(node->cmd.out, STDOUT_FILENO);
		close (node->cmd.out);

	#ifdef DEBUG
	#include <stdio.h>
	printf("stdout: %d\n", STDOUT_FILENO);
	#endif
	}
}

ssize_t	try_write(t_minishell *ms, int fd, char *src)
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
	{
		close(fd);
		error_exit(ms, NULL);
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
		error_exit(ms, "readline/write failed");
	}
	return (bytes);
}
