/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:46:51 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/23 17:03:50 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

const char**	get_redirections()
{
	static const char	*redirections[] = {">", ">>", "<", "<<", NULL};
	return (redirections);
}

const char**	get_quotes()
{
	static const char	*quotes[] = {"\"", "\'", NULL};
	return (quotes);
}

const char**	get_unsupported_chars()
{
	static const char	*characters[] = \
{"\\", ";", "&&", "&", "||", "*", "(", ")", "{", "}", "~", "#", "`", "!", NULL};
	return (characters);
}
