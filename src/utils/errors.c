/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:31:56 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/12 21:47:55 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "libft_str.h"
#include "cleanup.h"

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
	print_error(msg);
	exit(EXIT_FAILURE);
}

void	warning_syntax(t_minishell *ms, char *token)
{
	int	bytes;

	bytes = write(STDERR_FILENO, "\033[1;33m", 8);
	if (bytes != ERROR)
		bytes = write(\
STDERR_FILENO, "\033[1;33mminishell: syntax error near unxpected token `", 54);
	if (token && bytes != ERROR)
		bytes = write(STDERR_FILENO, token, ft_strlen(token));
	if (bytes != ERROR)
		bytes = write(STDERR_FILENO, "\'\n\033[0m", 7);
	if (bytes == ERROR)
		error_exit(ms, "write failed");
}

void	warning(t_minishell *ms, char *msg)
{
	int	bytes;

	bytes = write(STDERR_FILENO, "\033[1;33m", 8);
	if (bytes != ERROR)
		bytes = write(STDERR_FILENO, "minishell: ", 12);
	if (errno && bytes != ERROR)
	{
		perror(msg);
		errno = 0;
	}
	else if (msg && bytes != ERROR)
	{
		bytes = write(STDERR_FILENO, msg, ft_strlen(msg));
		if (bytes != ERROR)
			bytes = write(STDERR_FILENO, "\n", 1);
	}
	if (bytes != ERROR)
		bytes = write(STDERR_FILENO, "\033[0m", 5);
	if (bytes == ERROR)
		error_exit(ms, "write failed");
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

	bytes = write(STDERR_FILENO, "\033[1;31m", 8);
	if (errno && bytes != ERROR)
	{
		perror("minishell");
		errno = 0;
	}
	else if (bytes != ERROR)
	{
		bytes = write(STDERR_FILENO, "minishell: fatal error: ", 24);
		if (bytes != ERROR && msg)
			bytes = write(STDERR_FILENO, msg, ft_strlen(msg));
		if (bytes != ERROR)
			bytes = write(STDERR_FILENO, "\n", 1);
	}
	if (bytes != ERROR)
		bytes = write(STDERR_FILENO, "\033[0m", 5);
}
