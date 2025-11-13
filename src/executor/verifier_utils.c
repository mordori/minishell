/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifier_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:40:28 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/13 12:13:20 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "verifier_utils.h"

static char	*gen_fullpath(t_minishell *ms, char *dirpath, char *filename);
static bool	fmatch(struct stat *b, struct dirent **f, void **meta, char **p);

void	scan_dir(t_minishell *ms, char *dir, char *cmd_name, char **found)
{
	DIR				*dirstream;
	struct dirent	*file;
	struct stat		buffer;
	void			*metadata[4];

	file = NULL;
	metadata[MS] = ms;
	metadata[DIR_PATH] = dir;
	metadata[CMD_NAME] = cmd_name;
	ft_memset(&buffer, 0, sizeof(buffer));
	dirstream = opendir(dir);
	if (!dirstream)
		return ;
	metadata[DIRSTREAM] = dirstream;
	file = readdir(dirstream);
	while (file)
	{
		if (fmatch(&buffer, &file, metadata, found))
			break ;
	}
	closedir(dirstream);
}

static bool	fmatch(struct stat *b, struct dirent **f, void **meta, char **p)
{
	char	*full_path;

	full_path = gen_fullpath(meta[MS], meta[DIR_PATH], (*f)->d_name);
	stat(full_path, b);
	if ((b->st_mode & S_IFMT) == S_IFREG)
	{
		if (ft_strcmp((*f)->d_name, meta[CMD_NAME]) == 0)
		{
			*p = full_path;
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
	len = ft_strlen(dirpath) + ft_strlen(filename) + 2;
	full_path = alloc_volatile(ms, len);
	while (*dirpath && i < len)
		full_path[i++] = *dirpath++;
	full_path[i++] = '/';
	while (*filename && i < len)
		full_path[i++] = *filename++;
	full_path[i] = '\0';
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
	full_path = NULL;
	while (dir_list[i])
	{
		scan_dir(ms, dir_list[i], cmd_name, &full_path);
		if (full_path)
		{
			if (access(full_path, X_OK) == 0)
				return (full_path);
			ms->state.exit_status = ERROR_CMD_CANTEXEC;
		}
		i++;
	}
	return (full_path);
}
