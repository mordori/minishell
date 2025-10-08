/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:31:56 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/08 05:15:50 by myli-pen         ###   ########.fr       */
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

void	warning_input(t_minishell *ms, char *msg)
{
	int	bytes;

	bytes = write(STDERR_FILENO, "minishell: input error: ", 24);
	if (msg && bytes > 0)
		bytes = write(STDERR_FILENO, msg, ft_strlen(msg));
	if (bytes > 0)
		bytes = write(STDERR_FILENO, "\n", 1);
	if (bytes == ERROR)
		error_exit(ms, "write failed");
}

void	warning_syntax(t_minishell *ms, char *token)
{
	int	bytes;

	bytes = write(\
STDERR_FILENO, "minishell: syntax error near unxpected token `", 46);
	if (token && bytes > 0)
		bytes = write(STDERR_FILENO, token, ft_strlen(token));
	if (bytes > 0)
	bytes = write(STDERR_FILENO, "\'\n", 2);
	if (bytes == ERROR)
		error_exit(ms, "write failed");
}

void	warning_file(t_minishell *ms, char *filename)
{
	int	bytes;

	bytes = write(STDERR_FILENO, "minishell: ", 11);
	if (bytes != ERROR && errno)
	{
		perror(filename);
		errno = 0;
	}
	if (bytes == ERROR)
		error_exit(ms, "write failed");
}

void	warning_system(t_minishell *ms)
{
	int	bytes;

	bytes = write(\
STDERR_FILENO, "minishell: arena is at capacity: memory was not allocated\n", 59);
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

	if (errno)
	{
		perror("minishell");
		errno = 0;
	}
	else
	{
		bytes = write(STDERR_FILENO, "minishell: fatal error: ", 24);
		if (bytes != ERROR && msg)
			bytes = write(STDERR_FILENO, msg, ft_strlen(msg));
		if (bytes != ERROR)
			bytes = write(STDERR_FILENO, "\n", 1);
	}
}
