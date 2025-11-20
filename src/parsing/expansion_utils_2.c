/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:33:53 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/20 02:04:22 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "str_utils.h"
#include "arena.h"
#include "env.h"
#include "arena_list.h"

static inline size_t	split_word_len(char *src, char *ifs);

void	append_expanded_str(t_minishell *ms, t_ctx_exp *ctx)
{
	if (ctx->i + ft_strlen(ctx->temp) > EXP_BUF)
	{
		ctx->result = str_join(ms, ctx->result, ctx->buf, VOLATILE);
		ctx->i = 0;
		ft_memset(ctx->buf, 0, EXP_BUF);
	}
	if (ft_strlen(ctx->temp) > EXP_BUF)
		ctx->result = str_join(ms, ctx->result, ctx->temp, VOLATILE);
	else
	{
		ft_memcpy(ctx->buf + ctx->i, ctx->temp, ft_strlen(ctx->temp));
		ctx->i += ft_strlen(ctx->temp);
	}
}

void	append_chr(t_minishell *ms, char **src, t_ctx_exp *ctx)
{
	if (ctx->i > EXP_BUF)
	{
		ctx->result = str_join(ms, ctx->result, ctx->buf, VOLATILE);
		ctx->i = 0;
		ft_memset(ctx->buf, 0, EXP_BUF);
	}
	ctx->buf[ctx->i++] = **src;
	(*src)++;
}

void	split_words(t_minishell *ms, char *src, t_list **list)
{
	char	*ifs;
	char	*word;
	size_t	len;

	ifs = get_env_val(ms, "IFS");
	while (*src && is_whitespace(src, ifs))
		++src;
	while (*src)
	{
		len = split_word_len(src, ifs);
		word = alloc_volatile(ms, len + 1);
		ft_strlcpy(word, src, len + 1);
		lstadd_back(list, lstnew(ms, word));
		src += len;
		while (*src && is_whitespace(src, ifs))
			++src;
	}
}

char	*remove_quotes(t_minishell *ms, char *src)
{
	char	*result;
	size_t	i;
	size_t	j;
	char	quote;

	result = alloc_volatile(ms, ft_strlen(src) + 1);
	i = 0;
	j = 0;
	quote = 0;
	while (src[i])
	{
		if (src[i] == SQUOTE || src[i] == DQUOTE)
		{
			if (quote && src[i] != quote)
				result[j++] = src[i];
			else if (!quote)
				quote = src[i];
			else if (quote == src[i])
				quote = 0;
		}
		else
			result[j++] = src[i];
		++i;
	}
	return (result);
}

static inline size_t	split_word_len(char *src, char *ifs)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while(src[i])
	{
		if (!quote && is_whitespace(src + i, ifs))
			break ;
		if (!quote && (src[i] == SQUOTE || src[i] == DQUOTE))
			quote = src[i];
		else if (quote && src[i] == quote)
			quote = 0;
		++i;
	}
	return (i);
}
