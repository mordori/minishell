/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:46:51 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/20 03:53:44 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

const char	**get_redirections(void)
{
	static const char	*redirections[] = {">", ">>", "<", "<<", NULL};

	return (redirections);
}

const char	**get_quotes(void)
{
	static const char	*quotes[] = {"\"", "\'", NULL};

	return (quotes);
}

const char	**get_unsupported_chars(void)
{
	static const char	*characters[] = \
{">|", ">>|", "<<<", ";", "&&", "&", "||", NULL};

	return (characters);
}

const char	*get_ifs(void)
{
	static const char	ifs[] = " \t\n";

	return (ifs);
}
