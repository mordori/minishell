/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:52:48 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/06 17:26:26 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "arena.h"
#include "errors.h"
#include "libft_mem.h"
#include "lexer.h"
#include "parser.h"
#include "cleanup.h"
#include "libft_str.h"
#include "str_utils.h"
// #include "executor.h"

static inline void	startup(void);
static inline void	initialize(t_minishell *ms, char **envp);
static inline void	run(t_minishell *ms);
static inline void	get_prompt(t_minishell *ms, t_prompt *p);

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
	if (MEMORY < 0)
		error_exit(NULL, "defined memory amount is negative");
	if (argc > 1)
		error_exit(NULL, "too many arguments");
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
	ms->system = arena_create(ms, SYSTEM_MEMORY);
	ms->pool = arena_create(ms, MEMORY);
	if (!ms->system.base || !ms->pool.base)
		error_exit(ms, "arena creation failed");
	ms->state.envp = dup_envp_system(ms, envp);
	init_nodes();
	printf("%s\n", ms->state.envp[3]);
}

/**
 * @brief	WIP
 *
 * @param ms	Pointer to the minishell.
 */
static inline void	run(t_minishell *ms)
{
	t_token		**tokens;
	t_prompt	p;

	while (true)
	{
		arena_reset(&ms->pool);
		free(ms->line);
		get_prompt(ms, &p);
		ms->line = readline(p.prompt);
		if (!ms->line)
			break ;
		if (*ms->line)
			add_history(ms->line);
		ms->node = alloc_pool(ms, sizeof(*ms->node));
		tokens = create_tokens(ms->line, ms);
		if (!tokens || !parse_tokens(ms, tokens))
			continue ;
		//expand_variables(ms);
		setup_io(ms);
		// if (ms->node->cmd.args)
		// 	executor(ms);
		close_fds(ms);
		int ads = chdir("..");
		(void)ads;
	}
}

// TODO: set wrapper for getenv
static inline void	get_prompt(t_minishell *ms, t_prompt *p)
{
	p->fd = open("/etc/hostname", O_RDONLY);
	if (p->fd == ERROR)
		error_exit(ms, "open failed");
	p->len = read(p->fd, p->hostname, HOSTNAME_MAX);
	close(p->fd);
	if (p->len == ERROR)
		error_exit(ms, "read failed");
	p->hostname[p->len - 1] = 0;
	p->path = getcwd(p->cwd, sizeof(p->cwd));
	if (!p->path)
		error_exit(ms, "getcwd failed");
	p->home = "/";
	if (!ft_strncmp(p->path, getenv("HOME"), ft_strlen(getenv("HOME"))))
	{
		p->path += ft_strlen(getenv("HOME"));
		p->home = "~";
	}
	else if (!ft_strncmp(p->path, "/home", 5))
	{
		p->path = "";
		p->home = "/home";
	}
	else
		p->path = "";
	p->prompt = \
str_join(ms, \
str_join(ms, \
str_join(ms, \
str_join(ms, \
str_join(ms, \
str_join(ms, \
str_join(ms, \
"\033[38;5;90m", \
getenv("LOGNAME")), \
"@"), \
p->hostname), \
"\033[0m:\033[38;5;39m"), \
p->home), \
p->path), \
"\033[0m$ ");
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
