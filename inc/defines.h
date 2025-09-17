/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:55:02 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/17 19:49:18 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <stdbool.h>
# include <stdint.h>
# include <sys/types.h>
# include <stddef.h>
# include <limits.h>
# include <errno.h>

# define ERROR_INVALID_EXIT		255
# define ERROR_S_TERMINATED		130
# define ERROR_EXIT_ARG			128
# define ERROR_CMD_NOTFOUND		127
# define ERROR_CMD_CANTEXEC		126
# define ERROR_FORKING			-1
# define ERROR_GENERAL			1
# define ERROR_BUILTIN			2
# define ERROR_PIPELINE			3
# define SUCCESS				0
# define CMD					0

# define READLINE_PROMPT		"[minishell]$ "

typedef enum e_builtin_type	t_builtin;
typedef enum e_exec_mode	t_exec_mode;
typedef struct s_cmd		t_cmd;
typedef struct s_state		t_state;
typedef int					t_cmd_func(t_cmd, t_state);

enum e_builtin_type
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

enum e_exec_mode
{
	SIMPLE,
	PIPELINE
};

struct s_cmd
{
	t_exec_mode	mode;
	t_builtin	builtin_cmd;
	char		**args;
	t_cmd		*left;
	t_cmd		*right;
	int			pipe_fds[2];
	int			exit_status;
};

struct s_state
{
	int		pid_count; //can be parsed from the number of | characters
	pid_t	*pids;
	int		exit_status;
	char	**env_var;
};

#endif
