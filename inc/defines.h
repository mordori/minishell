/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:55:02 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/20 15:44:00 by myli-pen         ###   ########.fr       */
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

# define MEMORY_VARS			1048576UL
# ifndef MEM_UNIT
#  define MEM_UNIT				1024UL
# endif
# ifndef MEMORY
#  define MEMORY				16777216UL
# endif

# ifndef MAX_HEREDOC
#  define MAX_HEREDOC			16
# endif
# ifndef UUID_CHARS
#  define UUID_CHARS			36
# endif
# ifndef PATH_MAX
#  define PATH_MAX				4096
# endif
# ifndef NAME_MAX
#  define NAME_MAX				64
# endif
# ifndef EXP_BUF
#  define EXP_BUF				1024
# endif

# define RW_RW_RW_				0666
# define RW_______				0600

# define PROMPT					"> "

# define SQUOTE					'\''
# define DQUOTE					'\"'
# define MASK_SQ				1
# define MASK_DQ				2

extern volatile sig_atomic_t	g_signal;

typedef enum e_builtin_type		t_builtin;
typedef enum e_mode				t_mode;
typedef enum e_token_type		t_token_type;
typedef enum e_errors			t_errors;
typedef enum e_redir_type		t_redir_type;
typedef enum e_arena_type		t_arena_type;
typedef enum e_shell_mode		t_shell_mode;
typedef enum e_expand_mode		t_expand_mode;

typedef struct s_env			t_env;
typedef struct s_token			t_token;
typedef struct s_node			t_node;
typedef struct s_cmd			t_cmd;
typedef struct s_state			t_state;
typedef struct s_arena			t_arena;
typedef struct s_minishell		t_minishell;
typedef struct s_redir			t_redir;
typedef struct s_prompt			t_prompt;
typedef struct s_key_value		t_key_value;
typedef struct s_ctx_exp		t_ctx_exp;

typedef int						t_fun(t_minishell *, t_node *);

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

enum e_shell_mode
{
	AUTONOMOUS,
	INTERACTIVE
};

enum e_expand_mode
{
	EXPAND_DEFAULT,
	EXPAND_HEREDOC
};

struct s_redir
{
	t_redir_type	type;
	char			*file;
	char			*name;
	t_redir			*next;
};

struct s_key_value
{
	char	*k;
	char	*value;
	char	*delimiter;
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
	int				pos;
};

struct s_cmd
{
	t_builtin	builtin;
	char		*cmd;
	int			argc;
	char		**args;
	int			redir_in;
	int			redir_out;
	t_list		*redirs;
};

struct s_node
{
	t_cmd		cmd;
	t_node		*next;
	t_node		*prev;
	pid_t		pid;
};

struct s_state
{
	t_mode			mode;
	uint8_t			exit_status;
	t_env			*env;
	char			**envp;
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
	t_state				state;
	t_node				*node;
	char				pwd[PATH_MAX];
	t_shell_mode		mode;
	unsigned int		lineno;
	char				heredoc_file[UUID_CHARS + 5];
};

struct s_prompt
{
	char		*path;
	char		*home;
	char		hostname[NAME_MAX];
	char		logname[NAME_MAX];
	char		*prompt;
};

struct s_ctx_exp
{
	size_t		i;
	char		*result;
	char		*temp;
	char		quote;
	char		buf[EXP_BUF + 1];
};

const char	**get_redirections(void);
const char	**get_quotes(void);
const char	**get_unsupported_chars(void);
const char	*get_ifs(void);

#endif
