/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:58:00 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/24 10:39:50 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

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
		return (NULL); //FIXME: ERROR HANDLING: FAILED TO OPEN DIRECTORY.
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

void	check_fds(int *fds)
{
	(void) fds;
	//struct stat	buffer;
	//int			i;

	//fstat(fd[i], &buffer); for checking if FDs are open or closed. Requires
}

void	node_scrollback(t_minishell *ms)
{
	while (ms->node->prev)
		ms->node = ms->node->prev;
}

void	set_mode(t_minishell *ms)
{
	if (!ms->node->next)
		ms->state.mode = SIMPLE;
	else if (ms->node->next)
		ms->state.mode = PIPELINE;
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
