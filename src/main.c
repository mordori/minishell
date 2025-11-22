/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:52:48 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/22 23:12:12 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "arena.h"
#include "errors.h"
#include "libft_mem.h"
#include "parsing.h"
#include "file_utils.h"
#include "cleanup.h"
#include "str_utils.h"
#include "line_utils.h"
#include "executor.h"
#include "builtin.h"
#include "env.h"

volatile sig_atomic_t	g_signal = 0;

static inline void	initialize(t_minishell *ms, char **envp);
static inline void	run(t_minishell *ms);

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
		startup_msg();
	errno = 0;
	if (MEMORY < 0)
		error_exit(NULL, "defined memory amount is negative");
	if (argc > 1)
		error_exit(NULL, "too many arguments");
	ft_memset(&ms, 0, sizeof(ms));
	initialize(&ms, envp);
	run(&ms);
	status = ms.state.exit_status;
	clean(&ms);
	return (status);
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

	ms->vars = arena_create(ms, MEMORY_VARS, PERSISTENT);
	ms->pool = arena_create(ms, MEMORY, VOLATILE);
	if (!ms->vars.base || !ms->pool.base)
		error_exit(ms, "arena creation failed");
	envp_to_envll(ms, envp);
	ms->state.envp = envll_to_envp(ms, ms->state.env);
	if (isatty(STDIN_FILENO))
	{
		ms->mode = INTERACTIVE;
		rl_event_hook = rl_event;
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
	}
	errno = 0;
	signal(SIGPIPE, SIG_IGN);
	fd = try_open(ms, "/proc/sys/kernel/random/uuid", O_RDONLY, 0);
	if (fd == ERROR)
		error_exit(ms, "could not open /proc/sys/kernel/random/uuid");
	ft_memcpy(ms->heredoc_file, "/tmp/", 5);
	try_read(ms, fd, ms->heredoc_file + 5, UUID_CHARS);
	close(fd);
	set_env_defaults(ms, NULL);
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
		reset_context(ms);
		line = get_line(ms, get_prompt(ms, &p));
		if (g_signal == SIGINT)
			ms->state.exit_status = 130;
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
		executor(ms);
	}
}
