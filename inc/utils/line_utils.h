/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 04:06:14 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/19 21:07:23 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_UTILS_H
# define LINE_UTILS_H

# define _GNU_SOURCE

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

# include "defines.h"

char	*get_line(t_minishell *ms, char *prompt);
int		rl_event(void);
char	*get_prompt(t_minishell *ms, t_prompt *p);
void	set_names(t_minishell *ms, t_prompt *p);

#endif
