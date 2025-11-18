/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:52:41 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/18 03:05:36 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <stdlib.h>

# include "defines.h"
# include "builtin_utils.h"
# include "libft_list.h"
# include "env.h"
# include "cleanup.h"
# include "errors.h"
# include "str_utils.h"
# include "libft_str.h"
# include "file_utils.h"

//cd.c
int		cd(t_minishell *ms, t_node *node);
int		get_opwd(t_minishell *ms, t_node *node, char **path, bool is_1st);

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
