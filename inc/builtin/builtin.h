/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:52:41 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/16 16:50:50 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "defines.h"
# include "libft_list.h"
# include "env_utils.h"
# include "env.h"
# include <stdio.h>
# include <stdlib.h>

//cd.c
void	cd(t_cmd *cmd, t_state *state);

//echo.c
void	echo(t_cmd *cmd, t_state *state);

//pwd.c
void	pwd(t_cmd *cmd, t_state *state);

//export.c
void	export(t_cmd *cmd, t_state *state);

//unset.c
void	unset(t_cmd *cmd, t_state *state);

//env.c
void	env(t_cmd *cmd, t_state *state);

//exit.c
void	exitt(t_cmd *cmd, t_state *state);

#endif
