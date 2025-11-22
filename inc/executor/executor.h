/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:33:34 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/22 17:05:38 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"
# include "builtin.h"
# include "libft_str.h"
# include "str_utils.h"
# include "errors.h"
# include "executor_utils.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

//executor.c
void	executor(t_minishell *ms);
int		execute_simple(t_minishell *ms);
int		execute_pipeline(t_minishell *ms);

//cmd_processor.c
void	run_node(t_minishell *ms, t_node *node);
int		exec_builtin(t_minishell *ms, t_node *node);
int		exec_extern(t_minishell *ms, t_node *node);
void	set_env_defaults(t_minishell *ms, char **args);

//cmd_verification.c
int		command_verification(t_minishell *ms, t_node *node);

//exec_pipelines.c
void	spawn_and_run(t_minishell *ms, t_node *node, int in, int pipefd[2]);
void	try_fork(t_minishell *ms, pid_t *child_pid);

#endif
