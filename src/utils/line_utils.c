/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 03:53:51 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/20 23:23:17 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_utils.h"
#include "get_next_line.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "str_utils.h"
#include "errors.h"
#include "arena.h"
#include "env.h"
#include "io.h"

static inline char	*dup_line(\
t_minishell *ms, const char *src, unsigned int start, size_t len);

char	*get_line(t_minishell *ms, char *prompt)
{
	char	*line;
	char	*dup;

	if (ms->mode == AUTONOMOUS)
		get_next_line(ms, STDIN_FILENO, &line);
	if (ms->mode == INTERACTIVE)
		line = readline(prompt);
	if (line)
	{
		dup = dup_line(ms, line, 0, ft_strlen(line));
		if (ms->mode == INTERACTIVE)
			free(line);
		if (!dup)
			error_exit(ms, "dup line failed");
		++ms->lineno;
		return (dup);
	}
	return (line);
}

static inline char	*dup_line(\
t_minishell *ms, const char *src, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!src)
		return (NULL);
	i = 0;
	if (ft_strlen(src) > start)
		while (src[start + i] && i < len)
			++i;
	sub = arena_alloc(&ms->pool, (i + 1) * sizeof(char));
	if (sub)
		ft_memcpy(sub, &src[start], i);
	return (sub);
}

int	rl_event(void)
{
	int	bytes;

	if (g_signal == SIGINT)
	{
		bytes = write(1, "^C", 2);
		if (bytes == ERROR)
			perror("minishell");
		rl_done = 1;
		return (1);
	}
	return (0);
}

char	*get_prompt(t_minishell *ms, t_prompt *p)
{
	char	*home;

	home = get_env_val(ms, "HOME");
	if (!home)
	{
		p->home = "";
		p->path = ms->cwd;
	}
	else if (!ft_strncmp(ms->cwd, home, ft_strlen(home)))
	{
		p->home = "~";
		p->path = ms->cwd + ft_strlen(home);
	}
	else if (!ft_strncmp(ms->cwd, "/home", 5))
	{
		p->home = "/home";
		p->path = "";
	}
	else
	{
		p->home = "/";
		p->path = "";
	}
	p->prompt = \
str_join(ms, \
str_join(ms, \
str_join(ms, \
str_join(ms, \
str_join(ms, \
str_join(ms, \
str_join(ms, \
"\001\033[38;5;90m\002", \
p->logname), \
"@"), \
p->hostname), \
"\001\033[0m:\033[38;5;39m\002"), \
p->home), \
p->path), \
"\001\033[0m\002$ ");
	return (p->prompt);
}

void	set_names(t_minishell *ms, t_prompt *p)
{
	int		fd;
	ssize_t	len;

	p->logname = get_env_val(ms, "LOGNAME");
	if (!p->logname)
		p->logname = "user";
	fd = open("/etc/hostname", O_RDONLY);
	if (fd == ERROR)
	{
		if (errno == ENOENT)
		{
			ft_memcpy(p->hostname, "hostname", 8);
			return ;
		}
		error_exit(ms, "open failed");
	}
	len = try_read(ms, fd, p->hostname, HOSTNAME_MAX);
	close(fd);
	p->hostname[len - 1] = 0;
	if (ft_strchr(p->hostname, '.') - p->hostname > 0)
		p->hostname[ft_strchr(p->hostname, '.') - p->hostname] = 0;
}
