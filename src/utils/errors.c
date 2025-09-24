/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:31:56 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/24 04:59:38 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "string_utils.h"
#include "libft_str.h"
#include "main.h"

static inline void	print_error(char *file, int line, char *msg);

/**
 * @brief	General error function that cleans the program, prints a detailed
 * 			error message, and exits the program.
 *
 * @note	To be used with macro ERROR_EXIT(ms, msg).
 *
 * @param file	Name of the file where the error occurred.
 * @param line	Line where the error occurred.
 * @param ms	Pointer to the minishell.
 * @param msg	Error message.
 */
void	error_exit(char *file, int line, t_minishell *ms, char *msg)
{
	if (ms)
		clean_minishell(ms);
	print_error(file, line, msg);
	exit(EXIT_FAILURE);
}

/**
 * @brief	Prints a detailed error message.
 *
 * @param file	Name of the file where the error occurred.
 * @param line	Line where the error occurred.
 * @param msg	Error message.
 */
static inline void	print_error(char *file, int line, char *msg)
{
	char 	str_line[INT32_LENGTH + 1];
	size_t	len_line;
	int		bytes;

	len_line = int_to_str(line, str_line);
	bytes = write(STDERR_FILENO, "Error: ", 7);
	if (msg)
		bytes = write(STDERR_FILENO, msg, ft_strlen(msg));
	bytes = write(STDERR_FILENO, "\n", 1);
	bytes = write(STDERR_FILENO, file, ft_strlen(file));
	bytes = write(STDERR_FILENO, ", line: ", 8);
	bytes = write(STDERR_FILENO, str_line, len_line);
	bytes = write(STDERR_FILENO, "\n", 1);
	(void)bytes;
	perror("ERRNO");
	errno = 0;
}
