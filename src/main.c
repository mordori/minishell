/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:52:48 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/12 17:34:05 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "arena.h"
#include "errors.h"
#include "libft_mem.h"
#include "parsing.h"
#include "io.h"
#include "cleanup.h"
#include "str_utils.h"
#include "line_utils.h"
#include "executor.h"
#include "builtin.h"

volatile sig_atomic_t	g_signal = 0;

static inline void	startup(void);
static inline void	initialize(t_minishell *ms, char **envp);
static inline void	run(t_minishell *ms);
void				store_pwd(t_minishell *ms);

/**
 * @brief	Entry point to the program.
 *
 * @author		Mika Yli-Pentti		https://github.com/mordori
 * @author		Janne Valkama		https://github.com/cubicajupiter
 */
int	main(int argc, char *argv[], char **envp)
{
	t_minishell		ms;
	unsigned int	status;

	(void)argv;
	if (isatty(STDIN_FILENO))
		startup();
	else
		errno = 0;
#ifdef DEBUG
printf("\033[1;33m[DEBUG]\033[0m\n");
#endif
	if (MEMORY < 0)
		error_exit(NULL, "defined memory amount is negative");
	if (argc > 1)
		error_exit(NULL, "too many arguments");
	initialize(&ms, envp);
	run(&ms);
	status = ms.state.exit_status;
	clean(&ms);
	return (status);
}

void	sig_handler(int signum)
{
	g_signal = signum;
}

/**
 * @brief	Zero-initializes the minishell and creates memory arenas.
 *
 * @param	minishell Pointer to the minishell.
 * @param	envp Pointer for intake of OS environment variables.
 */
static inline void	initialize(t_minishell *ms, char **envp)
{
	int	fd;

	ft_memset(ms, 0, sizeof(*ms));
	ms->vars = arena_create(ms, MEMORY_VARS, PERSISTENT);
	ms->pool = arena_create(ms, MEMORY, VOLATILE);
	if (!ms->vars.base || !ms->pool.base)
		error_exit(ms, "arena creation failed");
	envp_to_envll(ms, envp);
	ms->state.envp = envll_to_envp(ms, ms->state.env);
	if (isatty(STDIN_FILENO))
	{
		ms->mode = INTERACTIVE;
		rl_catch_signals = 0;
		rl_event_hook = rl_event;
	}
	else
		errno = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	fd = try_open(ms, "/proc/sys/kernel/random/uuid", O_RDONLY, 0);
	if (fd == ERROR)
		error_exit(ms, "could not open /proc/sys/kernel/random/uuid");
	ft_memcpy(ms->heredoc_file, "/tmp/", 5);
	try_read(ms, fd, ms->heredoc_file + 5, UUID_CHARS);
	close(fd);
}

/**
 * @brief	WIP
 *
 * @param ms	Pointer to the minishell.
 */
static inline void	run(t_minishell *ms)
{
	char		*line;
	t_token		**tokens;
	t_prompt	p;

	set_prompt_names(ms, &p);
	while (true)
	{
		g_signal = 0;
		arena_reset(&ms->pool);
		store_pwd(ms);
		line = get_line(ms, get_prompt(ms, &p));
		if (g_signal == SIGINT)
			continue ;
		if (!line)
			exi(ms, NULL);
		if (ms->mode == INTERACTIVE && *line && *line != ' ')
			add_history(line);
		ms->node = alloc_volatile(ms, sizeof(t_node));
		tokens = create_tokens(line, ms);
		if (!tokens || !parse_tokens(ms, tokens))
			continue ;
		expand_variables(ms);
		setup_io(ms, ms->node);
		if (g_signal)
			ms->state.exit_status = 128 + g_signal;
		if (ms->node->cmd.args)
			executor(ms);
		close_all_fds(ms);
	}
}

void	store_pwd(t_minishell *ms)
{
	char	*cwd;
	char	buf[PATH_MAX];

	cwd = getcwd(buf, sizeof(buf));
	if (!cwd)
	{
		if (errno == ENOENT && ms->pwd[0])
			return ;
		else
			error_exit(ms, "get cwd failed");
	}
	ft_memcpy(ms->pwd, cwd, ft_strlen(cwd) + 1);
}

/**
 * @brief	Prints out a cool startup message. Wow!
 *
 * @return	Success status of the operation.
 */
static inline void	startup(void)
{
	if (printf("%s%s%s%s%s%s%s%s%s%s\n", \
"   ________   ________  ________   ________  _", \
"_______  ________  ________  _______   _______ \n", \
"  ╱        ╲ ╱        ╲╱    ╱   ╲ ╱        ╲╱ ", \
"       ╲╱    ╱   ╲╱        ╲╱       ╲ ╱       ╲\n", \
" ╱         ╱_╱       ╱╱         ╱_╱       ╱╱  ", \
"      _╱         ╱         ╱        ╱╱        ╱\n", \
"╱         ╱╱         ╱         ╱╱         ╱-  ", \
"      ╱         ╱        _╱        ╱╱        ╱ \n", \
"╲__╱__╱__╱ ╲________╱╲__╱_____╱ ╲________╱╲___", \
"_____╱╲___╱____╱╲________╱╲________╱╲________╱ \n") \
< 0)
		error_exit(NULL, NULL);
}
