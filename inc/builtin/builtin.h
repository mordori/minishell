/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:52:41 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/27 19:22:15 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "defines.h"
# include "libft_list.h"
# include "env.h"
# include "cleanup.h"
# include "errors.h"
# include "str_utils.h"
# include "libft_str.h"
# include <stdio.h>
# include <stdlib.h>

//cd.c
int		cd(t_minishell *ms);

//echo.c
int		echo(t_minishell *ms);

//pwd.c
int		pwd(t_minishell *ms);

//export.c
int		expo(t_minishell *ms);

//unset.c
int		unse(t_minishell *ms);

//env.c
int		env(t_minishell *ms);

//exit.c
int		exi(t_minishell *ms);

#endif
