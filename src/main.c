/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:52:48 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/23 20:56:50 by myli-pen         ###   ########.fr       */
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
	startup();
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

void	sig_handler(int sig)
{
	g_signal = sig;
}

/**
 * @brief	Zero-initializes the minishell and creates memory arenas.
 *
 * @param	minishell Pointer to the minishell.
 * @param	envp Pointer for intake of OS environment variables.
 */
static inline void	initialize(t_minishell *ms, char **envp)
{
	ft_memset(ms, 0, sizeof(*ms));
	ms->vars = arena_create(ms, MEMORY_VARS, PERSISTENT);
	ms->pool = arena_create(ms, MEMORY, VOLATILE);
	if (!ms->vars.base || !ms->pool.base)
		error_exit(ms, "arena creation failed");
	envp_to_envll(ms, envp, &ms->state);
	ms->state.envp = envll_to_envp(ms, ms->state.env);
	if (isatty(STDIN_FILENO))
	{
		ms->mode = INTERACTIVE;
		rl_catch_signals = 0;
		rl_event_hook = rl_event;
	}
	signal(SIGINT, sig_handler);
	signal(SIGINT, sig_handler);
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

	set_names(ms, &p);
	while (true)
	{
		g_signal = 0;
		arena_reset(&ms->pool);
		store_pwd(ms);
		line = get_line(ms, get_prompt(ms, &p));
		if (!line)
			exi(ms);
		if (*line && !g_signal)
			add_history(line);
		ms->node = alloc_volatile(ms, sizeof(t_node));
		tokens = create_tokens(line, ms);
		if (!tokens || !parse_tokens(ms, tokens))
			continue ;
		expand_variables(ms);
		setup_io(ms, ms->node);
		if (ms->node->cmd.args && !g_signal)
			executor(ms);
		close_fds(ms);
	}
}

void	store_pwd(t_minishell *ms)
{
	char	*cwd;
	char	buf[PATH_MAX];

	cwd = getcwd(buf, sizeof(ms->pwd));
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
