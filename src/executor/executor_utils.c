/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:58:00 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/18 18:20:23 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"
#include "libft_mem.h"

static char	*gen_fullpath(t_minishell *ms, char *dirpath, char *filename);

char	*scan_directory(t_minishell *ms, char *directory, char *cmd_name)
{
	DIR				*dirstream;
	struct dirent	*file;
	struct stat		buffer;
	char			*full_path;

	file = NULL;
	ft_memset(&buffer, 0, sizeof(buffer));
	dirstream = opendir(directory);
	if (!dirstream)
		return (NULL);
		//FIXME: ERROR HANDLING: FAILED TO OPEN DIRECTORY.
	file = readdir(dirstream);
	while (file) //NOTE: readdir returns NULL if nothing's left in dir.
	{
		full_path = gen_fullpath(ms, directory, file->d_name);
		stat(full_path, &buffer);
		if ((buffer.st_mode & S_IFMT) == S_IFREG)
		{
			if (ft_strcmp(file->d_name, cmd_name) == 0)
			{
				closedir(dirstream);
				return (full_path);
			}
		}
		file = readdir(dirstream);
	}
	closedir(dirstream);
	return (NULL);
}

static char	*gen_fullpath(t_minishell *ms, char *dirpath, char *filename)
{
	size_t	len;
	size_t	i;
	char	*full_path;

	i = 0;
	len = ft_strlen(dirpath) + ft_strlen(filename) + 1;
	full_path = alloc_volatile(ms, len);
	while (*dirpath && i < len)
		full_path[i++] = *dirpath++;
	full_path[i++] = '/';
	while (*filename && i < len)
		full_path[i++] = *filename++;
	return (full_path);
}
