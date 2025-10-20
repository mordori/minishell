/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 05:06:20 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/19 16:53:16 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "line_utils.h"
#include "libft_str.h"
#include "str_utils.h"
#include "errors.h"
#include "arena.h"

static inline void	eof_warning(t_minishell *ms, char *eof);

void	dup_io(t_node *node)
{
	if (node->cmd.in != STDIN_FILENO)
	{
		dup2(node->cmd.in, STDIN_FILENO);
		close (node->cmd.in);
	}
	if (node->cmd.out != STDOUT_FILENO)
	{
		dup2(node->cmd.out, STDOUT_FILENO);
		close (node->cmd.out);
	}
}

void	write_heredoc(t_minishell *ms, t_node *node, char *eof)
{
	char	*line;
	int		bytes;

	bytes = 0;
	while (true)
	{
		line = get_line(ms, PROMPT);
		if (!line || !ft_strcmp(line, eof) || g_signal)
			break ;
		bytes = write(node->cmd.in, line, ft_strlen(line));
		if (bytes != ERROR)
			bytes = write(node->cmd.in, "\n", 1);
		if (bytes == ERROR)
			break ;
	}
	if (!line)
		eof_warning(ms, eof);
	if (bytes == ERROR)
		error_exit(ms, "readline/write failed");
}

static inline void	eof_warning(t_minishell *ms, char *eof)
{
	char	*w;

	w = str_join(\
ms, "warning: here-document at line ", uint_to_str(ms, ms->lineno));
	w = str_join(ms, w, " delimited by end-of-file (wanted `");
	w = str_join(ms, w, eof);
	w = str_join(ms, w, "')");
	warning(ms, w);
}
