/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifier_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:40:28 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/28 11:18:38 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "verifier_utils.h"

static char	*gen_fullpath(t_minishell *ms, char *dirpath, char *filename);
static bool	fmatch(struct stat *b, struct dirent **f, char **p, void **meta);

char	*scan_directory(t_minishell *ms, char *directory, char *cmd_name)
{
	DIR				*dirstream;
	struct dirent	*file;
	struct stat		buffer;
	char			*full_path;
	void			*metadata[4];

	full_path = NULL;
	file = NULL;
	metadata[MS] = ms;
	metadata[DIR_PATH] = directory;
	metadata[CMD_NAME] = cmd_name;
	ft_memset(&buffer, 0, sizeof(buffer));
	dirstream = opendir(directory);
	if (!dirstream)
		return (NULL);
	metadata[DIRSTREAM] = dirstream;
	file = readdir(dirstream);
	while (file)
	{
		if (fmatch(&buffer, &file, &full_path, metadata))
			return (full_path);
	}
	closedir(dirstream);
	return (NULL);
}

static bool	fmatch(struct stat *b, struct dirent **f, char **p, void **meta)
{
	*p = gen_fullpath(meta[MS], meta[DIR_PATH], (*f)->d_name);
	stat(*p, b);
	if ((b->st_mode & S_IFMT) == S_IFREG)
	{
		if (ft_strcmp((*f)->d_name, meta[CMD_NAME]) == 0)
		{
			closedir(meta[DIRSTREAM]);
			return (true);
		}
	}
	*f = readdir(meta[DIRSTREAM]);
	return (false);
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

char	*path_verif(char *cmd_path)
{
	if (access(cmd_path, F_OK) == SUCCESS)
		return (cmd_path);
	return (NULL);
}

char	*environ_verif(t_minishell *ms, char *path, char *cmd_name)
{
	char	**dir_list;
	char	*full_path;
	int		i;

	i = 0;
	dir_list = str_split(ms, path, ':');
	while (dir_list[i])
	{
		full_path = scan_directory(ms, dir_list[i], cmd_name);
		if (full_path)
			return (full_path);
		i++;
	}
	return (NULL);
}
