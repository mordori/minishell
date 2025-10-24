/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:28:15 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/24 12:49:12 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include "defines.h"
# include "libft_str.h"
# include "libft_mem.h"
# include "str_utils.h"
# include "arena.h"
# include <dirent.h>
# include <sys/stat.h>

# define MS         0
# define DIR_PATH   1
# define CMD_NAME   2
# define DIRSTREAM  3

char	*scan_directory(t_minishell *ms, char *directory, char *cmd_name);
void	set_mode(t_minishell *ms);
void	check_fds(int *fds);
void	node_scrollback(t_minishell *ms);

#endif
