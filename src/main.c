/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:52:48 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/03 06:45:48 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "arena_utils.h"
#include "arena.h"
#include "errors.h"
#include "libft_mem.h"
#include "lexer.h"
#include "parser.h"
#include "redirection.h"
#include "expansion.h"
// #include "executor.h"

static inline void	startup(void);
static inline void	initialize(t_minishell *ms, char **envp);
static inline void	run(t_minishell *ms);
void	close_fds(t_minishell *ms);

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
	t_token		**tokens;

	ms->line = readline(PROMPT);
	while (true)
	{
		if (!*ms->line)
			break ;
		tokens = create_tokens(ms->line, ms);
		if (tokens)
		{
			ms->node = alloc_pool(ms, sizeof(*ms->node));
			if (parse_tokens(ms, tokens))
			{
				expand_variables(ms);
				redirect_io(ms);

				// TESTING
				// -------------------------------------------------------------

				while (ms->node)
				{
					printf("\n:args:\n");
					int i = 0;
					while (i < ms->node->cmd.argc)
						printf("%s\n", ms->node->cmd.args[i++]);
					printf("\n:redirs:\n");
					while (ms->node->cmd.redirs)
					{
						printf("%s\n", ((t_redir *)ms->node->cmd.redirs->content)->filename);
						ms->node->cmd.redirs = ms->node->cmd.redirs->next;
					}
					ms->node = ms->node->next;
				}

				// -------------------------------------------------------------

				//executor(ms);
				close_fds(ms);
			}
		}
		if (*ms->line)
			add_history(ms->line);
		free(ms->line);
		arena_reset(&ms->pool);
		ms->line = readline(PROMPT);
	}
}

void	close_fds(t_minishell *ms)
{
	while (ms->node)
	{
		if (ms->node->cmd.in > STDOUT_FILENO)
			close(ms->node->cmd.in);
		if (ms->node->cmd.out > STDOUT_FILENO)
			close(ms->node->cmd.out);
		ms->node = ms->node->next;
	}
}

/**
 * @brief	Destroys created memory arenas from minishell.
 */
void	clean(t_minishell *ms)
{
	if (!ms)
		return ;
	close_fds(ms);
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
