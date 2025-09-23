/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:52:48 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/23 22:54:57 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parsing.h"
#include "errors_utils.h"

static inline void	startup_msg();

int	main(void)
{


	startup_msg();
	initialize();
	prompt_input();
	return (EXIT_SUCCESS);
}

/**
 * @brief	Prints out a cool startup message. Wow!
 *
 * @return	Success status of the operation.
 */
static inline void	startup_msg()
{
	if (printf("%s%s%s%s%s%s%s%s%s%s\n",
"   ________   ________  ________   ________  _",
"_______  ________  ________  _______   _______ \n",
"  ╱        ╲ ╱        ╲╱    ╱   ╲ ╱        ╲╱ ",
"       ╲╱    ╱   ╲╱        ╲╱       ╲ ╱       ╲\n",
" ╱         ╱_╱       ╱╱         ╱_╱       ╱╱  ",
"      _╱         ╱         ╱        ╱╱        ╱\n",
"╱         ╱╱         ╱         ╱╱         ╱-  ",
"      ╱         ╱        _╱        ╱╱        ╱ \n",
"╲__╱__╱__╱ ╲________╱╲__╱_____╱ ╲________╱╲___",
"_____╱╲___╱____╱╲________╱╲________╱╲________╱ \n") \
< 0)
		error_exit(STARTUP_MSG);
}
