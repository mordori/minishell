/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 03:53:51 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/17 23:33:12 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_utils.h"
#include "get_next_line.h"
#include "libft_str.h"
#include "str_utils.h"
#include "errors.h"

char	*get_line(t_minishell *ms, char *prompt)
{
	char	*line;

	g_signal = 0;
	if (ms->mode == AUTONOMOUS)
		get_next_line(ms, STDIN_FILENO, &line);
	if (ms->mode == INTERACTIVE)
	{
		line = readline(prompt);
		if (line && *line)
			add_history(line);
	}
	if (line)
		++ms->lineno;
	return (line);
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
	if (g_signal == SIGQUIT)
	{
		return (1);
	}
	return (0);
}

char	*get_prompt(t_minishell *ms, t_prompt *p)
{
	char	*home;

	home = getenv("HOME");
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
getenv("LOGNAME")), \
"@"), \
p->hostname), \
"\001\033[0m:\033[38;5;39m\002"), \
p->home), \
p->path), \
"\001\033[0m\002$ ");
	return (p->prompt);
}

void	set_hostname(t_minishell *ms, t_prompt *p)
{
	int	fd;
	int	len;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == ERROR)
		error_exit(ms, "open failed");
	len = read(fd, p->hostname, HOSTNAME_MAX);
	close(fd);
	if (len < 0)
		error_exit(ms, "read failed");
	p->hostname[len - 1] = 0;
	if (ft_strchr(p->hostname, '.') - p->hostname > 0)
		p->hostname[ft_strchr(p->hostname, '.') - p->hostname] = 0;
}
