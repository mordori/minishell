/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:55:02 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/15 04:04:50 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define _GNU_SOURCE

# include <stdbool.h>
# include <stdint.h>
# include <sys/types.h>
# include <stddef.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

# include "libft_list.h"

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

# define MEMORY_VARS			524288UL
# ifndef MEM_UNIT
#  define MEM_UNIT				1024UL
# endif
# ifndef MEMORY
#  define MEMORY				1048576UL
# endif

# ifndef PATH_MAX
#  define PATH_MAX				4096
# endif

# ifndef HOSTNAME_MAX
#  define HOSTNAME_MAX			64
# endif

# define RW_RW_RW_				0666
# define RW_______				0600

# define PROMPT					"> "

//

extern volatile sig_atomic_t	g_signal;

typedef enum e_builtin_type		t_builtin;
typedef enum e_mode				t_mode;
typedef enum e_token_type		t_token_type;
typedef enum e_errors			t_errors;
typedef enum e_redir_type		t_redir_type;
typedef enum e_arena_type		t_arena_type;

typedef struct s_env			t_env;
typedef struct s_token			t_token;
typedef struct s_node			t_node;
typedef struct s_cmd			t_cmd;
typedef struct s_state			t_state;
typedef struct s_arena			t_arena;
typedef struct s_minishell		t_minishell;
typedef struct s_redir			t_redir;
typedef struct s_prompt			t_prompt;

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

enum e_token_type
{
	WORD,
	REDIR,
	PIPE,
	NEW_LINE
};

enum e_redir_type
{
	UNDEFINED,
	IN,
	OUT,
	OUT_APPEND,
	HEREDOC
};

enum e_arena_type
{
	PERSISTENT,
	VOLATILE
};

struct s_redir
{
	t_redir_type	type;
	char			*filename;
	t_redir			*next;
};

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
	t_env	*prev;
};

struct s_token
{
	char			*src;
	t_token_type	type;
	size_t			pos;
};

struct s_cmd
{
	t_builtin	builtin;
	char		*cmd;
	int			argc;
	char		**args;
	int			in;
	int			out;
	t_list		*redirs;
};

struct s_node
{
	t_cmd		cmd;
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
	t_env		*env;
	char		**envp;
};

struct s_arena
{
	char			*base;
	size_t			capacity;
	size_t			head;
	t_arena_type	type;
};

struct	s_minishell
{
	t_arena				vars;
	t_arena				pool;
	char				*line;
	t_state				state;
	t_node				*node;
	char				cwd[PATH_MAX];
	struct sigaction	sa;
};

struct s_prompt
{
	char		*path;
	char		*home;
	char		hostname[HOSTNAME_MAX];
};

const char**	get_redirections();
const char**	get_quotes();
const char**	get_unsupported_chars();

#endif
