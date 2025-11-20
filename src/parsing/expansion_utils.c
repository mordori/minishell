/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:33:53 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/20 02:12:31 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft_str.h"
#include "str_utils.h"
#include "arena.h"
#include "env.h"

static inline char	*mask_quotes(t_minishell *ms, char *src);

bool	expand(t_minishell *ms, char **src, t_ctx_exp *ctx, t_expand_mode mode)
{
	if (ctx->quote == SQUOTE || \
((*src)[1] != '?' && !ft_isalpha((*src)[1]) && ctx->quote))
	{
		append_chr(ms, src, ctx);
		return (false);
	}
	(*src)++;
	if (**src == '?')
	{
		ctx->temp = uint_to_str(ms, ms->state.exit_status);
		append_expanded_str(ms, ctx);
		(*src)++;
	}
	else
	{
		ctx->temp = join_var(ms, src, mode);
		append_expanded_str(ms, ctx);
	}
	return (true);
}

char	*join_var(t_minishell *ms, char **src, t_expand_mode mode)
{
	size_t	i;
	char	*key;
	char	*value;
	char	*result;

	i = 0;
	while ((*src)[i] && (*src)[i] != '$' && !is_whitespace(*src + i, "") && (*src)[i] != SQUOTE && (*src)[i] != DQUOTE)
		++i;
	key = str_sub(ms, VOLATILE, *src, i);
	*src += i;
	value = get_env_val(ms, key);
	if (mode == EXPAND_HEREDOC)
		return (value);
	result = mask_quotes(ms, value);
	return (result);
}

void	unmask_quotes(char *src)
{
	if (!src)
		return ;
	while (*src)
	{
		if (*src == MASK_SQ)
			*src = SQUOTE;
		else if (*src == MASK_DQ)
			*src = DQUOTE;
		++src;
	}
}

static inline char	*mask_quotes(t_minishell *ms, char *src)
{
	char	*result;
	char	*temp;

	result = alloc_volatile(ms, ft_strlen(src) + 1);
	temp = result;
	while (*src)
	{
		if (*src == SQUOTE)
			*temp = MASK_SQ;
		else if (*src == DQUOTE)
			*temp = MASK_DQ;
		else
			*temp = *src;
		++src;
		++temp;
	}
	return (result);
}
