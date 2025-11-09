/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:13:02 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/20 20:00:30 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "str_utils.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "errors.h"
#include "io.h"

static inline char	*join_lines(t_minishell *ms, char *line, const char *buf);
static inline char	*extract_line(t_minishell *ms, const char *buf);
static inline void	trimbuf(char *buf);
static inline size_t	linelen(const char *buf);

/**
 * Returns a line read from file descriptor `fd`.
 *
 * @param fd File descriptor to read from.
 * @param line Out line read.
 * @return Status code of the operation performed.
 */
int	get_next_line(t_minishell *ms, int fd, char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	ssize_t		bytes;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (GNL_ERROR);
	*line = extract_line(ms, buf);
	if (buf[0] && !*line)
		return (GNL_ERROR);
	while (!ft_strchr(buf, '\n'))
	{
		bytes = try_read(ms, fd, buf, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		*line = join_lines(ms, *line, buf);
	}
	trimbuf(buf);
	if (*line)
		return (GNL_OK);
	return (GNL_EOF);
}

/**
 * Joins an extracted string from the `buf` to the line that has no newline yet.
 *
 * @param buf Buffer of read characters.
 * @return Extracted string with a newline.
 */
static inline char	*join_lines(t_minishell *ms, char *line, const char *buf)
{
	char	*new_line;

	new_line = extract_line(ms, buf);
	if (!new_line)
		return (NULL);
	if (!line)
		return (new_line);
	return (str_join(ms, line, new_line, VOLATILE));
}

/**
 * Extracts a string from `buf`, NUL-terminating the result.
 *
 * @param buf Buffer of read characters.
 * @return Extracted string.
 */
static inline char	*extract_line(t_minishell *ms, const char *buf)
{
	if (!buf[0])
		return (NULL);
	return (str_sub(ms, VOLATILE, buf, linelen(buf)));
}

/**
 * Removes a string with a newline from `buf`, then NUL-terminates the result.
 *
 * @param buf Buffer of read characters.
 */
static inline void	trimbuf(char *buf)
{
	size_t	len_nl;
	size_t	len_buf;

	len_nl = linelen(buf);
	len_buf = ft_strlen(buf);
	ft_memcpy(buf, buf + len_nl, len_buf);
	buf[len_buf - len_nl] = '\0';
}

/**
 * Counts the number of characters in a `buf` to an included newline,
 * or to NUL if not found.
 *
 * @param buf Buffer of read characters.
 * @return Number of characters in a buffer to an included newline,
 * or to NUL if not found.
 */
static inline size_t	linelen(const char *buf)
{
	size_t	len_nl;

	len_nl = 0;
	while (buf[len_nl] != '\n' && buf[len_nl])
		++len_nl;
	if (buf[len_nl] == '\n')
		++len_nl;
	return (len_nl);
}
