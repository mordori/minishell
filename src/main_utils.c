/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:41:33 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/23 01:31:46 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "arena.h"
#include "errors.h"
#include "libft_mem.h"
#include "cleanup.h"
#include "env.h"

void	reset_context(t_minishell *ms)
{
	errno = 0;
	g_signal = 0;
	arena_reset(&ms->pool);
	store_pwd(ms);
}

void	sig_handler(int signum)
{
	g_signal = signum;
}

void	store_pwd(t_minishell *ms)
{
	char	*cwd;
	char	buf[PATH_MAX];

	cwd = get_env_val(ms, "PWD");
	if (!*cwd)
		cwd = getcwd(buf, sizeof(buf));
	if (!cwd)
	{
		if (errno == ENOENT && ms->pwd[0])
			return ;
		warning(ms, "getcwd failed");
		cwd = "undefined";
	}
	ft_memcpy(ms->pwd, cwd, ft_strlen(cwd) + 1);
}

/**
 * @brief	Prints out a cool startup message. Wow!
 *
 * @return	Success status of the operation.
 */
void	startup_msg(void)
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
