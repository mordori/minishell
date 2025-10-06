/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:33:34 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/06 03:01:52 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"
# include <fcntl.h>
# include <unistd.h>

//executor.c
int		executor(t_minishell *ms);
void	execute_simple(t_cmd *cmd, t_state *shell_state);
void	execute_pipeline(t_cmd **cmd, t_state *shell_state);
int		exec_builtin(t_cmd *cmd, t_state *shell_state);

//child_processes.c
int		exec_extern(t_cmd *cmd);

//exec_pipeline.c
int		create_pipes(t_state *shell);
int		spawn_and_run(t_state *shell, t_cmd *cmd);

//redirections.c
//int		redirect_input
//int		redirect_output

//executor_utils.c
bool	is_builtin(t_cmd *command);
int		fork_child(pid_t *child_pid, t_state *shell);



#endif
