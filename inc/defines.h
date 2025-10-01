/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:55:02 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/01 02:52:27 by myli-pen         ###   ########.fr       */
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

# define INT32_LENGTH			11
# define INT64_LENGTH			20

# define SYSTEM_SIZE			256
# ifndef POOL_SIZE
#  define POOL_SIZE				1024
# endif

# define PROMPT					"\033[0;36m[minishell]\033[0m$ "

typedef enum e_builtin_type		t_builtin;
typedef enum e_mode				t_mode;
typedef enum e_type				t_type;
typedef enum e_errors			t_errors;

typedef struct s_env			t_env;
typedef struct s_token			t_token;
typedef struct s_cmd			t_cmd;
typedef struct s_state			t_state;
typedef struct s_node			t_node;
typedef struct s_mem_arena		t_mem_arena;
typedef struct s_minishell		t_minishell;

typedef int		t_cmd_func(t_cmd, t_state);

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
	OPERATOR
};

struct s_env
{
	int		total_len;
	char	*key;
	char	*value;
	t_env	*next;
};

struct s_token
{
	char		*src;
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
	pid_t		pids[30587]; //could just be dynamically allocated instead of ulimit -u limit on Maximum child process number.
	int			exit_status;
	char		**envp;
};

struct s_cmd
{
	t_builtin	builtin;
	char		*cmd;
	char		**argv;
};

struct s_mem_arena
{
	char		*base;
	size_t		capacity;
	size_t		head;
};

struct	s_minishell
{
	t_mem_arena	system;
	t_mem_arena	pool;
	char		*line;
	t_state		*state;
	bool		exit;
};

const char**	get_redirs();
const char**	get_pipe();
const char**	get_quotes();

#endif
