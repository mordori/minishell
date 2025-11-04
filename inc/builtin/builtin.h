/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:52:41 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/04 11:16:54 by jvalkama         ###   ########.fr       */
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
int		cd(t_minishell *ms, t_node *node);

//echo.c
int		echo(t_minishell *ms, t_node *node);

//pwd.c
int		pwd(t_minishell *ms, t_node *node);

//export.c
int		expo(t_minishell *ms, t_node *node);

//unset.c
int		unse(t_minishell *ms, t_node *node);

//env.c
int		env(t_minishell *ms, t_node *node);

//exit.c
int		exi(t_minishell *ms, t_node *node);

#endif
