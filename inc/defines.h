/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:55:02 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/24 04:26:13 by myli-pen         ###   ########.fr       */
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
# define ERROR_REDIR			4
# define SUCCESS				0
# define CMD					0

# define INT32_LENGTH			11			// byte
# define INT64_LENGTH			20			// byte

# define MEM_SIZE_SYSTEM		256
# define MEM_SIZE_POOL			1024

# define PROMPT					"\033[0;36m[minishell]\033[0m$ "

# define ERROR_EXIT(ms, msg)	error_exit(__FILE__, __LINE__, ms, msg)

typedef enum e_builtin_type	t_builtin;
typedef enum e_mode			t_mode;
typedef enum e_type			t_type;

typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;
typedef struct s_state		t_state;
typedef struct s_node		t_node;
typedef struct s_mem_arena	t_mem_arena;
typedef struct s_minishell	t_minishell;

typedef int					t_cmd_func(t_cmd, t_state);

enum e_builtin_type
{
	FALSE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

enum e_mode
{
	SIMPLE,
	PIPELINE
};

enum e_type
{
	WORD,
	QUOTED_WORD,
	REDIRECTION,
	OPERATOR
};

struct s_token
{
	char		*token;
	t_type		type;
};

struct s_node
{
	t_cmd		*cmd;
	t_node		*next;
	t_node		*prev;
	int			pipe_fds[2];
};

struct s_state
{
	t_mode		mode;
	int			child_count; //can be parsed from the number of | characters
	pid_t		*pids;
	int			exit_status;
	char		**env_var;
};

struct s_cmd
{
	t_builtin	builtin;
	char		*cmd;
	char		**args;
};

struct s_mem_arena
{
	char		*base;
	size_t		capacity;
	size_t		head;
};

struct	s_minishell
{
	t_mem_arena	mem_system;
	t_mem_arena	mem_pool;
	bool		exit;
};

#endif
