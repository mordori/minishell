/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:55:02 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/18 17:49:40 by jvalkama         ###   ########.fr       */
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

typedef int cmd_func(t_cmd, t_state);

typedef struct s_state
{
	t_mode			mode;
	int				child_count; //can be parsed from the number of | characters
	pid_t			*pids;
	int				exit_status;
	char			**env_var;
}	t_state;

typedef struct s_cmd
{
	t_builtin		builtin;
	char			*cmd;
	char			**args;
	int				exit_status;
}	t_cmd;

typedef struct s_node
{
	t_cmd			*left;
	t_node			*next;
	t_node			*prev;
	int				pipe_fds[2];
}	t_node;

typedef enum e_mode
{
	SIMPLE,
	PIPELINE
}	t_mode;

typedef enum e_builtin_type
{
	FALSE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtin;

#endif
