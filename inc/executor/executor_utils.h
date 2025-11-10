/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:28:15 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/07 15:22:26 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include "defines.h"
# include "libft_str.h"
# include "libft_mem.h"
# include "str_utils.h"
# include "arena.h"
# include "errors.h"
# include <dirent.h>
# include <sys/stat.h>

void	set_mode(t_minishell *ms);
void	check_fds(int *fds);
void	node_scrollback(t_minishell *ms);

#endif
