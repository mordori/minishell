/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifier_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:20:54 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/13 12:13:22 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERIFIER_UTILS_H
# define VERIFIER_UTILS_H

# include <sys/stat.h>

# define MS         0
# define DIR_PATH   1
# define CMD_NAME   2
# define DIRSTREAM  3

char	*scan_directory(t_minishell *ms, char *directory, char *cmd_name);
char	*path_verif(char *cmd_path);
char	*environ_verif(t_minishell *ms, char *path, char *cmd_name);

#endif
