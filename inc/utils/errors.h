/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:32:48 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/25 14:38:17 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include "defines.h"

void	error_exit(t_minishell *ms, char *msg);

#endif
