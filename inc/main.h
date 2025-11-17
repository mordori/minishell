/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:53:19 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/17 20:34:58 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <readline/readline.h>
# include <readline/history.h>

# include "defines.h"

void	sig_handler(int sig);
void	store_pwd(t_minishell *ms);
void	reset_context(t_minishell *ms);
void	startup_msg(void);

#endif
