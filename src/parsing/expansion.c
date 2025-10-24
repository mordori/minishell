/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:07:18 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/23 17:53:20 by myli-pen         ###   ########.fr       */
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

static inline char		**expand_args(t_minishell *ms, char **args);
// static inline t_list	*expand_redirs(t_list *redirs);

void	expand_variables(t_minishell *ms)
{
	t_node	*head;

	head = ms->node;
	while(head)
	{
		if (head->cmd.args)
			expand_args(ms, head->cmd.args);
		//head->cmd.redirs = expand_redirs(head->cmd.redirs);
		head = head->next;
	}
}

static inline char	*expand_str(t_minishell *ms, char *src)
{
	char	*str;
	char	*ptr;
	char	*result;
	size_t	i;
	char	*var;

	str = ft_strchr(src, '$');
	if (!str)
		return(src);
	i = str - src;
	result = alloc_volatile(ms, sizeof(char) * (i + 1));
	ft_memcpy(result, src, i);
	while (str++)
	{
		if (!*str)
			result = str_join(ms, result, "$", VOLATILE);
		if (*str == '?')
		{
			result = str_join(ms, result, uint_to_str(ms, ms->state.exit_status), VOLATILE);
			++str;
		}
		if (*str == '\"' || *str == '\'')
		{
			++str;
			i = 0;
			while (str[i] && str[i] != '\"')
				++i;
			result = str_join(ms, result, str_sub(ms, VOLATILE, str, i), VOLATILE);
			str += i;
			if (*str == '\"' || *str == '\'')
				++str;
		}
		else
		{
			i = 0;
			while (str[i] && str[i] != '$')
				++i;

			var = get_env_val(ms, str_sub(ms, VOLATILE, str, i));
			result = str_join(ms, result, var, VOLATILE);
			str += i;
		}
		ptr = ft_strchr(str, '$');
		if (ptr)
			result = str_join(ms, result, str_sub(ms, VOLATILE, str, ptr - str), VOLATILE);
		else
			break ;
		str = ptr;
	}
	result = str_join(ms, result, str, VOLATILE);
#ifdef DEBUG
	printf("%s\n", result);
#endif
	return (result);
}

static inline char	**expand_args(t_minishell *ms, char **raw_args)
{
	while (*raw_args)
	{
		*raw_args = expand_str(ms, *raw_args);
		++raw_args;
	}
	return (raw_args);
}


// READ HEREDOC IN TOO



// static inline t_list	*expand_redirs(t_list *raw_redirs)
// {
// 	t_list	*redirs;
// 	//t_redir	*r;

// 	redirs = raw_redirs;
// 	while (raw_redirs)
// 	{
// 		//r = (t_redir *)raw_redirs->content;
// 		raw_redirs = raw_redirs->next;
// 	}
// 	return (redirs);
// }
