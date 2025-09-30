/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 04:09:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/01 01:18:53 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "string_utils.h"
#include "mem_arena.h"
#include "errors.h"
#include "mem_utils.h"
#include "libft_str.h"

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
	i = 0;
	// Debug
	while (tokens[i])
	{
		printf("%s ", tokens[i]->src);
		printf("%d\n", tokens[i]->type);
		++i;
	}
	return (tokens);
}

static inline void	tokenize(t_token *token)
{
	if (cmp_type(get_quotes(), token->src))
		token->type = ARGUMENT;
	else if (cmp_type(get_redirs(), token->src))
		token->type = REDIRECTION;
	else if (cmp_type(get_pipe(), token->src))
		token->type = PIPE;
	else
		token->type = COMMAND;
}

bool	cmp_type(const char **types, const char *src)
{
	while (*types)
	{
		if (*src == **types)
			return (true);
		++types;
	}
	return (false);
}

bool	cmp_types(const char *src)
{
	if (\
cmp_type(get_quotes(), src) || \
cmp_type(get_redirs(), src) || \
cmp_type(get_pipe(), src))
		return (true);
	return (false);
}
