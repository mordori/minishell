/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:31:56 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/02 20:31:08 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "string_utils.h"
#include "libft_str.h"
#include "main.h"

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

	bytes = write(STDERR_FILENO, "minishell: input error, ", 24);
	if (msg && bytes > 0)
		bytes = write(STDERR_FILENO, msg, ft_strlen(msg));
	if (bytes > 0)
		bytes = write(STDERR_FILENO, "\n", 1);
	if (bytes == ERROR)
		error_exit(ms, "warning write failed");
}

void	*warning_syntax(t_minishell *ms, char *msg)
{
	int	bytes;

	bytes = write(\
STDERR_FILENO, "minishell: syntax error near unxpected token `", 46);
	if (msg && bytes > 0)
		bytes = write(STDERR_FILENO, msg, ft_strlen(msg));
	if (bytes > 0)
	bytes = write(STDERR_FILENO, "\'\n", 2);
	if (bytes == ERROR)
		error_exit(ms, "warning write failed");
	return (NULL);
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

	bytes = write(STDERR_FILENO, "-----------------------------------\n", 36);
	bytes = write(STDERR_FILENO, "minishell: fatal error: ", 24);
	if (msg)
		bytes = write(STDERR_FILENO, msg, ft_strlen(msg));
	bytes = write(STDERR_FILENO, "\n", 1);
	(void)bytes;
	perror("ERRNO");
	errno = 0;
}
