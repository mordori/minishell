/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:52:41 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/25 14:43:31 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "defines.h"
# include <stdio.h>
# include <stdlib.h>

//cd.c
void	cd(t_cmd *cmd, t_state *shell_state);

//echo.c
int		echo(t_state *shell, t_cmd *cmd);

//pwd.c
void	pwd(t_cmd *cmd, t_state *shell_state);

#endif
