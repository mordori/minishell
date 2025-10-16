/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:33:34 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/14 15:05:24 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"
# include "builtin.h"
# include "libft_str.h"
# include "executor_utils.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

//executor.c
int		executor(t_minishell *ms);
void	execute_simple(t_cmd *cmd, t_state *shell_state);
void	execute_pipeline(t_cmd **cmd, t_state *shell_state);

//cmd_processor.c
void	run_node(t_cmd *cmd, t_state *state);
void	exec_builtin(t_cmd *cmd, t_state *state);
int		exec_extern(t_cmd *cmd, t_state *state);

//cmd_verification.c
void	command_verification(t_minishell *ms);

//exec_pipelines.c
int		spawn_and_run(t_node *node, t_state *state, int count, int *prev_fd);
int		create_pipe(t_node *node, int *prev_fd);
int		fork_child(pid_t *child_pid);
int		io_directions(t_node *node, int prev_fd);
int		close_parent_pps(t_node *node);

//redirections.c
//int		redirect_input
//int		redirect_output


#endif
