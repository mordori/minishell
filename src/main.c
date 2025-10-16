/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:52:48 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/16 05:11:07 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "arena.h"
#include "errors.h"
#include "libft_mem.h"
#include "lexer.h"
#include "parser.h"
#include "io.h"
#include "cleanup.h"
#include "str_utils.h"
#include "line_utils.h"
// #include "executor.h"

volatile sig_atomic_t	g_signal = 0;

static inline void	startup(void);
static inline void	initialize(t_minishell *ms, char **envp);
static inline void	run(t_minishell *ms);
void	store_cwd(t_minishell *ms);

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
	startup();
#ifdef DEBUG
printf("\033[1;33m[DEBUG]\033[0m\n");
#else
printf("Remove #ifdef DEBUG directives before submission\n");
#endif
	if (MEMORY < 0)
		error_exit(NULL, "defined memory amount is negative");
	if (argc > 1)
		error_exit(NULL, "too many arguments");
	initialize(&ms, envp);
	run(&ms);
	clean(&ms);
	return (EXIT_SUCCESS);
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
	ms->state.envp = dup_envp_system(ms, envp);
	//init_nodes(ms);
	if (isatty(STDIN_FILENO))
	{
		ms->mode = INTERACTIVE;
		rl_catch_signals = 0;
		rl_event_hook = rl_event;
	}
	signal(SIGINT, sig_handler);
	signal(SIGINT, sig_handler);
}

#ifdef DEBUG
static inline void	debug_print_args_redirs(t_minishell *ms, t_token **tokens)
{
	t_node	*node;

	node = ms->node;
	printf("\n");
	int i = 0;
	while (node)
	{
		printf("[%d] ARGS:\t", i);
		while (tokens[1] && node->cmd.args && *node->cmd.args)
		{
			printf("%s, ", *node->cmd.args);
			node->cmd.args++;
		}
		printf("\n[%d] REDIRS:\t", i);
		while (tokens[1] && node->cmd.redirs)
		{
			printf("%s, ", ((t_redir *)node->cmd.redirs->content)->filename);
			node->cmd.redirs = node->cmd.redirs->next;
		}
		printf("\n\n");
		node = node->next;
		++i;
	}
}
#endif

/**
 * @brief	WIP
 *
 * @param ms	Pointer to the minishell.
 */
static inline void	run(t_minishell *ms)
{
	t_token		**tokens;
	t_prompt	p;

	set_hostname(ms, &p);
	while (true)
	{
		store_cwd(ms);
		ms->line = get_line(ms, get_prompt(ms, &p));
		if (!ms->line)
			break ;
		arena_reset(&ms->pool);
		ms->node = alloc_volatile(ms, sizeof(t_node));
		tokens = create_tokens(ms->line, ms);
		if (!tokens || !parse_tokens(ms, tokens))
			continue ;
		expand_variables(ms);
		setup_io(ms);
#ifdef DEBUG
debug_print_args_redirs(ms, tokens);
#endif
		// if (ms->node->cmd.args)
		// 	executor(ms);
		free(ms->line);
		ms->line = NULL;
		close_fds(ms);
	}
}

void	store_cwd(t_minishell *ms)
{
	char	*cwd;
	char	buf[PATH_MAX];

	cwd = getcwd(buf, sizeof(buf));
	if (!cwd)
	{
		if (errno == ENOENT && ms->cwd[0])
			return ;
		else
			error_exit(ms, "get cwd failed");
	}
	ft_memcpy(ms->cwd, cwd, strlen(cwd));
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
