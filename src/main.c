/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:52:48 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/23 16:23:06 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parsing.h"
#include "libft_io.h"

static inline void	splash_msg();

int	main(void)
{
	splash_msg();
	initialize();
	prompt_input();
	return (EXIT_SUCCESS);
}

static inline void	splash_msg()
{
	ft_printf("   ________   ________  ________   ________  ________  ________  ________  _______   _______ \n");
	ft_printf("  ╱        ╲ ╱        ╲╱    ╱   ╲ ╱        ╲╱        ╲╱    ╱   ╲╱        ╲╱       ╲ ╱       ╲\n");
	ft_printf(" ╱         ╱_╱       ╱╱         ╱_╱       ╱╱        _╱         ╱         ╱        ╱╱        ╱\n");
	ft_printf("╱         ╱╱         ╱         ╱╱         ╱-        ╱         ╱        _╱        ╱╱        ╱ \n");
	ft_printf("╲__╱__╱__╱ ╲________╱╲__╱_____╱ ╲________╱╲________╱╲___╱____╱╲________╱╲________╱╲________╱ \n");
	ft_printf("\n");
}
