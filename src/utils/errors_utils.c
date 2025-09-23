/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:31:56 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/23 22:53:32 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors_utils.h"
#include "string_utils.h"

static inline void			print_error(int code);
static inline void			destroy_arenas(void);

void	error_exit(int code)
{
	print_error(code);
	destroy_arenas();
	exit(EXIT_FAILURE);
}

static inline void	print_error(int code)
{
	char	str_code[INT32_LENGTH + 1];
	size_t	len_code;
	int		bytes;

	len_code = int_to_str(code, str_code);
	bytes = write(STDERR_FILENO, "Error point: ", 13);
	bytes = write(STDERR_FILENO, str_code, len_code);
	bytes = write(STDERR_FILENO, "\n", 1);
	(void)bytes;
	perror("Message");
	errno = 0;
}

static inline void	destroy_arenas(void)
{
	int	i;

	i = 0;
	(void)i;
}
