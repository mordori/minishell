/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:58:00 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/16 16:50:53 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*scan_directory(char *directory)
{
	DIR				*dirstream;
	struct dirent	*file;
	struct stat		*buffer;

	dirstream = opendir(directory);
	if (!dirstream)
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
				return (ft_strjoin(dir_list[i], cmd_name)); //FIXME: muuten hyva mutta ft_strjoin malloccaa
			}
		}
		file = readdir(dirstream);
	}
	closedir(dirstream);
	return (NULL);
}
