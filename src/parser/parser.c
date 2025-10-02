/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:15:08 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/02 03:58:57 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "errors.h"
#include "libft_str.h"
#include "arena_list.h"
#include "arena_utils.h"

t_command	*parse(t_minishell *ms, t_token **tokens)
{
	t_token		*t;
	t_token		*prev;
	t_list		*args;
	t_command	*cmd;
	t_command	*head;
	int			i;

	cmd = alloc_pool(ms, sizeof(*cmd));
	head = cmd;
	args = NULL;
	while (*tokens)
	{
		t = *tokens;
		if (t->pos > 0)
			prev = *(tokens - 1);
		if (t->type != WORD && t->pos > 0 && (prev->type == REDIRECTION || prev->type == PIPE))
			error_syntax(t->src);
		else if (t->type == PIPE)
		{
			if (t->pos == 0 || !args)
				error_syntax(t->src);
			else
			{
				head->argc = lstsize(args);
				head->args = alloc_pool(ms, sizeof(*head->args) * (head->argc + 1));
				i = 0;
				while (i < head->argc)
					head->args[i++] = (args++)->content;
				i = 0;
				while (i < head->argc)
					printf("%s\n", head->args[i++]);
				head->next = alloc_pool(ms, sizeof(*cmd));
				head = head->next;
				args = NULL;
			}
		}
		if (t->type == REDIRECTION)
		{

		}
		if (t->type == WORD)
		{
			if (t->pos == 0 || (!args && (prev->type == WORD || (prev->pos != 0 && !ft_strcmp(prev->src, "|")))))
				args = lstnew(ms, t->src);
			else if (args && prev->type == WORD)
				lstadd_back(&args, lstnew(ms, t->src));
		}
		++tokens;
	}
	return (cmd);
}
