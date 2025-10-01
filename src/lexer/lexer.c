/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 04:09:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/01 04:19:37 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "string_utils.h"
#include "mem_arena.h"
#include "errors.h"
#include "mem_utils.h"

static inline void	tokenize(t_token *token);

t_token	**create_tokens(char *src, t_minishell *ms)
{
	t_token	**tokens;
	char	**srcs;
	int		i;

	srcs = str_split(ms, src);
	if (!srcs)
		return (NULL);
	i = 0;
	while (srcs[i])
		++i;
	tokens = alloc_pool(ms, sizeof(*tokens) * (i + 1));
	i = 0;
	while (srcs[i])
	{
		tokens[i] = alloc_pool(ms, sizeof(*tokens[i]));
		tokens[i]->src = srcs[i];
		tokenize(tokens[i]);
		++i;
	}
	return (tokens);
}

static inline void	tokenize(t_token *token)
{
	if (is_operator(token->src))
		token->type = OPERATOR;
	else
		token->type = WORD;
}

bool	cmp_strs(const char **types, const char *src)
{
	while (*types)
	{
		if (*src == **types)
			return (true);
		++types;
	}
	return (false);
}

bool	is_operator(const char *src)
{
	if (cmp_strs(get_redirs(), src) || cmp_strs(get_pipe(), src))
		return (true);
	return (false);
}

bool	is_quote(const char *src)
{
	if (cmp_strs(get_quotes(), src))
		return (true);
	return (false);
}
