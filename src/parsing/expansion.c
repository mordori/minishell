/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:07:18 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/29 00:48:54 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "str_utils.h"
#include "arena_list.h"
#include "arena.h"
#include "env.h"

#ifdef DEBUG
#include <stdio.h>
#endif

static inline void	expand_args(t_minishell *ms, char **args);
static inline void	expand_redirs(t_minishell *ms, t_list *redirs);

void	expand_variables(t_minishell *ms)
{
	t_node	*node;

	node = ms->node;
	while(node)
	{
		if (node->cmd.args)
			expand_args(ms, node->cmd.args);
		expand_redirs(ms, node->cmd.redirs);
		node = node->next;
	}
}

static inline void	expand_args(t_minishell *ms, char **raw_args)
{
	char	**args;

	args = raw_args;
	while (*args)
	{
		expand_str(ms, args, EXPAND_DEFAULT);
		*args = remove_quotes(ms, *args);
		++args;
	}
}

static inline void	expand_redirs(t_minishell *ms, t_list *raw_redirs)
{
	t_list	*redirs;
	t_redir	*r;

	redirs = raw_redirs;
	while (redirs)
	{
		r = (t_redir *)redirs->content;
		if (r->type != HEREDOC)
		{
			expand_str(ms, &r->file, EXPAND_DEFAULT);
			r->file = remove_quotes(ms, r->file);
		}
		redirs = redirs->next;
	}
}

bool	expand(t_minishell *ms, char **str, char **result, char *quote, t_expand_mode mode)
{
	char	*ptr;

	if (!**str)
	{
		*result = str_join(ms, *result, "$", VOLATILE);
		return (false);
	}
	if (**str == '?')
		*result = str_join(ms, *result, uint_to_str(ms, ms->state.exit_status), VOLATILE);
	else if (**str == '$')
		*result = str_join(ms, *result, uint_to_str(ms, (unsigned int)getpid()), VOLATILE);
	else if (**str == '\"' || **str == '\'')
		join_var_name(ms, str, result, mode);
	else
		join_var(ms, str, result, *quote, mode);
	++(*str);
	ptr = ft_strchr(*str, '$');
	if (!ptr)
		return (false);
	*result = str_join(ms, *result, str_sub(ms, VOLATILE, *str, ptr - *str), VOLATILE);
	if (!*quote && ptr - *str > 2 && (*(ptr - 1) == '\'' || *(ptr - 1) == '\"'))
		*quote = *(ptr - 1);
	*str = ptr;
	return (true);
}

void	expand_str(t_minishell *ms, char **src, t_expand_mode mode)
{
	char	*str;
	char	*result;
	size_t	i;
	char	quote;

	str = ft_strchr(*src, '$');
	if (!str)
		return ;
	i = str - *src;
	result = alloc_volatile(ms, i + 1);
	ft_memcpy(result, *src, i);
	quote = 0;
	if (i > 0 && ((*src)[i - 1] == '\'' || (*src)[i - 1] == '\"'))
		quote = (*src)[i - 1];
	while (str++)
	{
		if (!expand(ms, &str, &result, &quote, mode))
			break;
	}
	result = str_join(ms, result, str, VOLATILE);
	*src = result;
}

char	*remove_quotes(t_minishell *ms, char *src)
{
	char	*result;
	char	*ptr;
	size_t	i;

	ptr = find_quote(src);
	if (!ptr)
		return (src);
	result = alloc_volatile(ms, ptr - src + 1);
	ft_memcpy(result, src, ptr - src);
	src = ptr + 1;
	while (*src)
	{
		i = 0;
		while (src[i] != *ptr)
			++i;
		result = str_join(ms, result, str_sub(ms, VOLATILE, src, i), VOLATILE);
		src += i + 1;
		ptr = find_quote(src);
		if (!ptr)
			break;
		result = str_join(ms, result, str_sub(ms, VOLATILE, src, ptr - src), VOLATILE);
		src = ptr;
	}
	result = str_join(ms, result, src, VOLATILE);
	return (result);
}
