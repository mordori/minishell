/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 05:06:20 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/05 10:49:06 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "libft_str.h"
#include "errors.h"

void	dup_io(t_node *node)
{

	#ifdef DEBUG
	#include <stdio.h>
	printf("1st check inside dup_io, read fd: %d, write fd: %d, of node: %s with pid: %d\n", node->cmd.in, node->cmd.out, node->cmd.cmd, node->pid);
	#endif

	if (node->cmd.in != STDIN_FILENO)
	{
		dup2(node->cmd.in, STDIN_FILENO);
		close (node->cmd.in);
	}
	if (node->cmd.out != STDOUT_FILENO)
	{
		dup2(node->cmd.out, STDOUT_FILENO);
		close (node->cmd.out);
	}

	#ifdef DEBUG
	#include <stdio.h>
	printf("2nd check inside dup_io, read fd: %d of node: %s with pid: %d\n", node->cmd.in, node->cmd.cmd, node->pid);
	#endif

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
		error_exit(ms, NULL);
	return (bytes);
}

ssize_t	try_write_endl(t_minishell *ms, int fd, char *src)
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
	bytes = write(fd, "\n", 1);
	if (bytes != 1)
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
		error_exit(ms, "readline/write failed");
	return (bytes);
}
