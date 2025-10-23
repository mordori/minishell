/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:33:34 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/23 15:35:28 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"
# include "builtin.h"
# include "libft_str.h"
# include "str_utils.h"
# include "executor_utils.h"
# include "errors.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

//executor.c
int		executor(t_minishell *ms);
void	execute_simple(t_minishell *ms);
void	execute_pipeline(t_minishell *ms);
int		wait_pids(t_state *state);
//DEBUG
int    ft_log(char *file_name, char *func_name, char *data);

//cmd_processor.c
void	run_node(t_minishell *ms);
void	exec_builtin(t_minishell *ms);
void	exec_extern(t_minishell *ms);

//cmd_verification.c
void	command_verification(t_minishell *ms, t_node *node);

//exec_pipelines.c
int		spawn_and_run(t_minishell *ms, int count, int *prev_fd);
int		create_pipe(t_node *node, int *prev_fd);
int		fork_child(pid_t *child_pid);
int		io_directions(t_node *node, int prev_fd);
int		close_parent_pps(t_node *node);

//redirections.c
//int		redirect_input
//int		redirect_output


#endif
