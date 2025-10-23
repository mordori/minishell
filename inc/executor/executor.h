/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:33:34 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/23 20:06:24 by jvalkama         ###   ########.fr       */
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

# define READ	0
# define WRITE	1

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
int		spawn_and_run(t_minishell *ms, int count, int *prev_read);
void	fork_child(t_minishell *ms, pid_t *child_pid);

//redirections.c
//int		redirect_input
//int		redirect_output


#endif
