/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:52:48 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/04 04:10:53 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "arena_utils.h"
#include "arena.h"
#include "errors.h"
#include "libft_mem.h"
#include "lexer.h"
#include "parser.h"
#include "io.h"
#include "expansion.h"
#include "cleanup.h"
#include "libft_str.h"
#include "str_utils.h"
// #include "executor.h"

static inline void	startup(void);
static inline void	initialize(t_minishell *ms, char **envp);
static inline void	run(t_minishell *ms);
static inline char	*get_prompt(t_minishell *ms);

/**
 * @brief	Entry point to the program.
 *
 * @author		Mika Yli-Pentti		https://github.com/mordori
 * @author		Janne Valkama		https://github.com/cubicajupiter
 */
int	main(int argc, char *argv[], char **envp)
{
	t_minishell	ms;

	(void)argv;
	if (argc > 1)
		error_exit(NULL, "too many arguments");
	if (MEMORY < 1024)
		error_exit(NULL, "not enough memory (1024 KiB minimum)");
	startup();
	initialize(&ms, envp);
	run(&ms);
	clean(&ms);
	return (EXIT_SUCCESS);
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
	ms->state.envp = envp;
	ms->system = arena_create(SYSTEM_MEMORY);
	ms->pool = arena_create(MEMORY);
	if (!ms->system.base || !ms->pool.base)
		error_exit(ms, "arena creation failed");
}

/**
 * @brief	WIP
 *
 * @param ms	Pointer to the minishell.
 */
static inline void	run(t_minishell *ms)
{
	t_token	**tokens;

	while (true)
	{
		free(ms->line);
		arena_reset(&ms->pool);
		ms->line = readline(get_prompt(ms));
		if (*ms->line)
			add_history(ms->line);
		if (!*ms->line) // for debugging leaks - remove later
			break ;
		ms->node = alloc_pool(ms, sizeof(*ms->node));
		tokens = create_tokens(ms->line, ms);
		if (!tokens || !parse_tokens(ms, tokens))
			continue ;
		expand_variables(ms);
		set_io(ms);
		//executor(ms);
		close_fds(ms);
	}
}

static inline char	*get_prompt(t_minishell *ms)
{
	static char	cwd[PATH_MAX];
	char		*prompt;

	prompt = getcwd(cwd, sizeof(cwd));
	if (!prompt)
		error_exit(ms, "getcwd failed");
	prompt = ft_strchr(prompt + 1, '/');
	prompt = ft_strchr(prompt + 1, '/');
	prompt = str_join(ms, "\033[38;5;90mminishell\033[0m:\033[38;5;39m~/", prompt + 1);
	prompt = str_join(ms, prompt, "\033[0m$ ");
	return (prompt);
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
		error_exit(NULL, "startup message failed");
}
