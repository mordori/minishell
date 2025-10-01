/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:32:48 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/01 03:10:09 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include "defines.h"

void	error_exit(t_minishell *ms, char *msg);
void	error_input(t_minishell *ms, char *msg);
void	error_syntax(t_minishell *ms, char *msg);

#endif
