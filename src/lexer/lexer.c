/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 04:09:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/19 06:38:39 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "arena.h"
#include "errors.h"
#include "str_utils.h"

static inline void	set_token_type(t_token *token);

t_token	**create_tokens(char *src, t_minishell *ms)
{
	t_token	**tokens;
	char	**srcs;
	int		i;

	srcs = tokenize(ms, src);
	if (!srcs)
		return (NULL);
	i = 0;
	while (srcs[i])
		++i;
	tokens = alloc_volatile(ms, sizeof(t_token *) * (i + 2));
	i = 0;
	while (srcs[i])
	{
		tokens[i] = alloc_volatile(ms, sizeof(t_token));
		tokens[i]->src = srcs[i];
		tokens[i]->pos = i;
		set_token_type(tokens[i]);
		++i;
	}
	tokens[i] = alloc_volatile(ms, sizeof(t_token));
	tokens[i]->src = "newline";
	tokens[i]->pos = i;
	tokens[i]->type = NEW_LINE;
	return (tokens);
}

static inline void	set_token_type(t_token *token)
{
	if (is_redirection(token->src))
		token->type = REDIR;
	else if (is_pipe(token->src))
		token->type = PIPE;
	else if (is_newline(token->src))
		token->type = NEW_LINE;
	else
		token->type = WORD;
}
