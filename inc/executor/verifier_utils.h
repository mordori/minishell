/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifier_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:20:54 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/27 13:21:26 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERIFIER_UTILS_H
# define VERIFIER_UTILS_H

char	*scan_directory(t_minishell *ms, char *directory, char *cmd_name);
char	*path_verif(char *cmd_path);
char	*environ_verif(t_minishell *ms, char *path, char *cmd_name);

#endif
