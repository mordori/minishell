/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:46:51 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/30 21:58:07 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

const char**	get_redirs()
{
	static const char	*redirections[] = {">", ">>", "<", "<<", NULL};
	return (redirections);
}

const char**	get_pipe()
{
	static const char	*pipe[] = {"|", NULL};
	return (pipe);
}

const char**	get_quotes()
{
	static const char	*quotes[] = {"\"", "\'", NULL};
	return (quotes);
}

