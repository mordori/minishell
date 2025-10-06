/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 04:09:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/06 08:30:15 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "arena.h"
#include "errors.h"
#include "str_utils.h"

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
	tokens = alloc_pool(ms, sizeof(*tokens) * (i + 2));
	i = 0;
	while (srcs[i])
	{
		tokens[i] = alloc_pool(ms, sizeof(t_token));
		tokens[i]->src = srcs[i];
		tokens[i]->pos = i;
		tokenize(tokens[i]);
		++i;
	}
	tokens[i] = alloc_pool(ms, sizeof(t_token));
	tokens[i]->src = "newline";
	tokens[i]->pos = i;
	tokens[i]->type = NEW_LINE;
	return (tokens);
}

static inline void	tokenize(t_token *token)
{
	if (is_redirection(token->src))
		token->type = REDIR;
	else if (is_pipe(token->src))
		token->type = PIPE;
	else
		token->type = WORD;
}
