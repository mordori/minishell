/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 04:09:10 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/02 16:52:22 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "arena_utils.h"
#include "arena.h"
#include "errors.h"
#include "string_utils.h"
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
	tokens = alloc_pool(ms, sizeof(*tokens) * (i + 2));
	i = 0;
	while (srcs[i])
	{
		tokens[i] = alloc_pool(ms, sizeof(*tokens[i]));
		tokens[i]->src = srcs[i];
		tokens[i]->pos = i;
		tokenize(tokens[i]);
		++i;
	}
	tokens[i] = alloc_pool(ms, sizeof(*tokens[i]));
	tokens[i]->src = "newline";
	tokens[i]->pos = i;
	tokens[i]->type = NEW_LINE;
	return (tokens);
}

static inline void	tokenize(t_token *token)
{
	if (is_redirection(token->src))
		token->type = REDIRECTION;
	else if (is_pipe(token->src))
		token->type = PIPE;
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
	if (is_redirection(src) || is_pipe(src))
		return (true);
	return (false);
}

bool	is_redirection(const char *src)
{
	if (cmp_strs(get_redirections(), src))
		return (true);
	return (false);
}

bool	is_pipe(const char *src)
{
	if (!ft_strcmp(src, "|"))
		return (true);
	return (false);
}

bool	is_quote(const char *src)
{
	if (cmp_strs(get_quotes(), src))
		return (true);
	return (false);
}
