/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 04:09:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/26 01:43:02 by myli-pen         ###   ########.fr       */
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
	static const char	*quotes[] = {"\"", "\'"};
	static const char	*pipe[] = {"|"};
	static const char	*redirections[] = \
{">", ">>", ">>", "<", "<<", "<<<"};

	if (*token->src == *quotes[0])
		token->type = QUOTED_WORD;
	else if (*token->src == *redirections[0])
		token->type = REDIRECTION;
	else if (*token->src == *pipe[0])
		token->type = PIPE;
	else
		token->type = WORD;
}
