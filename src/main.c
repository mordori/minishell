/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:52:48 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/25 15:02:04 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"
#include "errors.h"
#include "libft_mem.h"
#include "mem_arena.h"
#include "lexer.h"

static inline void	startup(void);
static inline void	initialize(t_minishell *ms);
static inline void	run(t_minishell *ms);

/**
 * @brief	Entry point to the program.
 *
 * @author		Mika Yli-Pentti		https://github.com/mordori
 * @author		Janne Valkama		https://github.com/cubicajupiter
 */
int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;

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
 */
static inline void	initialize(t_minishell *ms, char **envp)
{
	ft_memset(ms, 0, sizeof(*ms));
	ms->mem_system = arena_create(MEM_SIZE_SYSTEM);
	ms->mem_pool = arena_create(MEM_SIZE_POOL);
	if (!ms->mem_system.base || !ms->mem_pool.base)
		error_exit(ms, "Memory arena creation", __FILE__, __LINE__);
	init_env(ms, envp);
}

/**
 * @brief	WIP
 *
 * @param ms	Pointer to the minishell.
 */
static inline void	run(t_minishell *ms)
{
	char	*line;
	t_token	*tokens;

	line = readline(PROMPT);
	while (line)
	{
		tokens = create_tokens(line);
		(void)tokens;
		// parse(line);
		// expand();
		// redirect();
		// execute();
		arena_reset(&ms->mem_pool);
		free(line);
		error_exit(ms, "Test error", __FILE__, __LINE__);
		if (ms->exit)
			break ;
		line = readline(PROMPT);
	}
}

/**
 * @brief	Destroys created memory arenas from minishell.
 */
void	clean(t_minishell *ms)
{
	if (!ms)
		return ;
	arena_destroy(&ms->mem_pool);
	arena_destroy(&ms->mem_system);
}

/**
 * @brief	Prints out a cool startup message. Wow!
 *
 * @return	Success status of the operation.
 */
static inline void	startup(void)
{
	if (printf("%s%s%s%s%s%s%s%s%s%s\n",
"   ________   ________  ________   ________  _",
"_______  ________  ________  _______   _______ \n",
"  ╱        ╲ ╱        ╲╱    ╱   ╲ ╱        ╲╱ ",
"       ╲╱    ╱   ╲╱        ╲╱       ╲ ╱       ╲\n",
" ╱         ╱_╱       ╱╱         ╱_╱       ╱╱  ",
"      _╱         ╱         ╱        ╱╱        ╱\n",
"╱         ╱╱         ╱         ╱╱         ╱-  ",
"      ╱         ╱        _╱        ╱╱        ╱ \n",
"╲__╱__╱__╱ ╲________╱╲__╱_____╱ ╲________╱╲___",
"_____╱╲___╱____╱╲________╱╲________╱╲________╱ \n") \
< 0)
		error_exit(NULL, "Startup message print", __FILE__, __LINE__);
}
