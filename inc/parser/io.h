/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:06:24 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/05 00:59:04 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>

# include "defines.h"

void	setup_io(t_minishell *ms);

#endif
