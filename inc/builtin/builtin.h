/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:52:41 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/23 16:55:33 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "defines.h"
# include "libft_list.h"
# include "env_utils.h"
# include "env.h"
# include "cleanup.h"
# include "errors.h"
# include "str_utils.h"
# include "libft_str.h"
# include <stdio.h>
# include <stdlib.h>

//cd.c
void	cd(t_minishell *ms);

//echo.c
void	echo(t_minishell *ms);

//pwd.c
void	pwd(t_minishell *ms);

//export.c
void	expo(t_minishell *ms);

//unset.c
void	unse(t_minishell *ms);

//env.c
void	env(t_minishell *ms);

//exit.c
void	exi(t_minishell *ms);

#endif
