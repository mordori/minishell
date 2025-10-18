/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:58:00 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/18 05:17:14 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"
#include "libft_mem.h"

char	*scan_directory(t_minishell *ms, char *directory, char *cmd_name)
{
	DIR				*dirstream;
	struct dirent	*file;
	struct stat		buffer;

	file = NULL;
	ft_memset(&buffer, 0, sizeof(buffer));
	dirstream = opendir(directory);
	if (!dirstream)
		return (NULL);
		//FIXME: add logic: FAILED TO OPEN DIRECTORY.
	file = readdir(dirstream);
	while (file) //NOTE: readdir returns NULL if nothing's left in dir.
	{
		if (stat(file->d_name, &buffer) == -1) //FIXME: stat requires full path, d_name not enough.
			//FIXME: add logic: FAILED TO STAT FILE.
		if ((buffer.st_mode & S_IFMT) == S_IFREG)
		{
			if (ft_strcmp(file->d_name, cmd_name) == 0)
			{
				closedir(dirstream);
				return (str_join(ms, directory, cmd_name));
			}
		}
		file = readdir(dirstream);
	}
	closedir(dirstream);
	return (NULL);
}
