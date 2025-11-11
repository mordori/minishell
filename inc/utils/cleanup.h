/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 22:27:44 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/03 22:32:19 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "defines.h"

void	clean(t_minishell *ms);
void	close_all_fds(t_minishell *ms);
void	close_fds(t_node *node);

#endif
