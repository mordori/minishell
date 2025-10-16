/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:39 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/16 16:50:54 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	redirect_input(char *file)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ERROR_REDIR);
	if (dup2(fd, STDIN_FILENO))
	{
		close(fd);
		return (ERROR_REDIR);
	}
	close(fd);
	return (SUCCESS);
}

int	redirect_output(char *file, bool is_append)
{
	int		flags;
	int		fd;

	flags = O_WRONLY | O_CREAT;
	if (is_append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd == -1)
		return (ERROR_REDIR);
	if (dup2(fd, STDOUT_FILENO))
	{
		close(fd);
		return (ERROR_REDIR);
	}
	close(fd);
	return (SUCCESS);
}


//FIX: implement a temp file system. RUN HEREDOCS IN CHILD PROCESS FOR CTRL+C (EXIT) TO WORK RIGHT.
//NOTE: creating a temp file might be useful.
// heredocs also fork into child processes.
// fork() a child process,
// open() a temp file for write,
// write() the expanded here doc to it. The contents depends on the iteration.
// close() it,
// open() it again read-only,
// unlink(), so it will be deleted after it's closed,
// dup2(4, 0) the resulting descriptor so that the new process has the temp file as stdin,
// Executes the /bin/cat process,
// cat reads the file from disk, writing its contents to stdout,
// [ https://www.oilshell.org/blog/2016/10/18.html ]
// although DASH just places lines in kernel buffer through pipe_fd[1]
int	heredoc(char *delimiter)
{
	char	*line;
	int		pipe_fd[2];
	int		line_len;

	if (pipe(pipe_fd));
		return (ERROR_REDIR);
	while (true)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		line_len = ft_strlen(line);
		write(pipe_fd[1], line, line_len);
		write(1, '\n', 1);
	}
	//TEST: in the middle of pipeline execution in Bash
	//NOTE: needs pipe_fd[0] duplicated to STDIN_FILENO for pipeline separately mayube
	return (SUCCESS);
}
