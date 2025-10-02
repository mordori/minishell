/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:52:48 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/01 18:09:11 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parser.h"
#include "errors.h"
#include "libft_mem.h"
#include "mem_arena.h"
#include "lexer.h"
#include "mem_utils.h"

static inline void	startup(void);
static inline void	initialize(t_minishell *ms, char **envp);
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

	(void)ac;
	(void)av;
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
	(void)envp;
	ft_memset(ms, 0, sizeof(*ms));
	ms->system = arena_create(SYSTEM_SIZE);
	ms->pool = arena_create(POOL_SIZE);
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

	ms->line = readline(PROMPT);
	while (true)
	{
		// reg sig handlesre
		tokens = create_tokens(ms->line, ms);
		if (tokens)
		{
			parse(tokens);
			// expand();
			// redirect(); HEREDOC
			// sig handler
			// execute();
			if (ms->exit)
				break ;
		}
		if (*ms->line)
			add_history(ms->line);
		free(ms->line);
		arena_reset(&ms->pool);
		ms->line = readline(PROMPT);
	}
}

/**
 * @brief	Destroys created memory arenas from minishell.
 */
void	clean(t_minishell *ms)
{
	if (!ms)
		return ;
	arena_destroy(&ms->pool);
	arena_destroy(&ms->system);
	rl_clear_history();
	if (ms->line)
		free(ms->line);
	ms->line = NULL;
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
