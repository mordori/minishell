/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 04:09:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/24 20:16:35 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "string_utils.h"
#include "mem_arena.h"
#include "errors.h"

static inline void	tokenize_src(t_token *token);

t_token	**create_tokens(char *src, t_minishell *ms)
{
	t_token	**tokens;
	char	**srcs;
	int		i;

	srcs = str_split(src, &ms->pool);
	if (!srcs)
		error_exit(ms, "Source string split failed", __FILE__, __LINE__);
	i = 0;
	while (srcs[i])
		++i;
	tokens = arena_alloc(&ms->pool, sizeof(t_token *) * (i + 1));
	if (!tokens)
		error_exit(ms, "Tokens array alloc failed", __FILE__, __LINE__);
	i = 0;
	while (srcs[i])
	{
		tokens[i] = arena_alloc(&ms->pool, sizeof(t_token));
		if (!tokens[i])
			error_exit(ms, "Token alloc failed", __FILE__, __LINE__);
		tokens[i]->src = srcs[i];
		tokenize_src(tokens[i]);
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

static inline void	tokenize_src(t_token *token)
{
	if (*token->src == '\"')
		token->type = QUOTED_WORD;
	else if (*token->src == '<' || *token->src == '>')
		token->type = REDIRECTION;
	else if (*token->src == '|')
		token->type = OPERATOR;
	else
		token->type = WORD;
}
