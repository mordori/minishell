/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:28:15 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/01 14:28:55 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include "defines.h"
# include "libft_str.h"
# include "str_utils.h"
# include <dirent.h>
# include <sys/stat.h>

char	*scan_directory(t_minishell *ms, char *directory, char *cmd_name);

#endif
