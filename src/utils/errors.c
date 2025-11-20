/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:31:56 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/20 22:47:09 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "libft_str.h"
#include "str_utils.h"
#include "cleanup.h"
#include "file_utils.h"

static inline void	print_error(char *msg);

/**
 * @brief	General error function that cleans the program, prints a detailed
 * 			error message, and exits the program.
 *
 * @note	To be used with built-in macros __FILE__ and __LINE__.
 *
 * @param file	Name of the file where the error occurred.
 * @param line	Line where the error occurred.
 * @param ms	Pointer to the minishell.
 * @param msg	Error message.
 */
void	error_exit(t_minishell *ms, char *msg)
{
	if (ms)
		clean(ms);
	if (msg)
		print_error(msg);
	else if (errno)
	{
		perror("minishell");
		errno = 0;
	}
	exit(EXIT_FAILURE);
}

void	eof_warning(t_minishell *ms, char *eof, unsigned int lineno)
{
	char	*w;

	w = str_join(\
ms, "warning: here-document at line ", uint_to_str(ms, lineno), VOLATILE);
	w = str_join(ms, w, " delimited by end-of-file (wanted `", VOLATILE);
	w = str_join(ms, w, eof, VOLATILE);
	w = str_join(ms, w, "')", VOLATILE);
	warning(ms, w);
}

void	warning_syntax(t_minishell *ms, char *src)
{
	char	*msg;

	msg = "undefined source";
	if (src)
		msg = src;
	try_write(ms, STDERR_FILENO, "\001\033[1;33m\002");
	try_write(ms, STDERR_FILENO, \
"minishell: syntax error near unxpected token `");
	try_write(ms, STDERR_FILENO, msg);
	try_write(ms, STDERR_FILENO, "\'\n\001\033[0m\002");
	ms->state.exit_status = 2;
}

void	warning(t_minishell *ms, char *src)
{
	char	*msg;

	msg = "undefined source";
	if (src)
		msg = src;
	if (ms->mode == INTERACTIVE)
		try_write(ms, STDERR_FILENO, "\001\033[1;33m\002");
	try_write(ms, STDERR_FILENO, "minishell: ");
	if (errno)
	{
		perror(msg);
		errno = 0;
	}
	else
	{
		try_write(ms, STDERR_FILENO, msg);
		try_write(ms, STDERR_FILENO, "\n");
	}
	if (ms->mode == INTERACTIVE)
		try_write(ms, STDERR_FILENO, "\001\033[0m\002");
}

/**
 * @brief	Prints a detailed error message.
 *
 * @param file	Name of the file where the error occurred.
 * @param line	Line where the error occurred.
 * @param msg	Error message.
 */
static inline void	print_error(char *msg)
{
	int	bytes;

	bytes = write(STDERR_FILENO, "\001\033[1;31m\002", 8);
	if (bytes != ERROR)
	{
		if (errno)
		{
			perror("minishell");
			errno = 0;
		}
		else
		{
			bytes = write(STDERR_FILENO, "minishell: ", 11);
			if (bytes != ERROR && msg)
				bytes = write(STDERR_FILENO, msg, ft_strlen(msg));
			if (bytes != ERROR)
				bytes = write(STDERR_FILENO, "\n", 1);
		}
		if (bytes != ERROR)
			bytes = write(STDERR_FILENO, "\001\033[0m\002", 5);
	}
}
