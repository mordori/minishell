/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:15:08 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/02 20:29:05 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "errors.h"
#include "libft_str.h"
#include "arena_list.h"
#include "arena_utils.h"

// t_command	*parse_tokens(t_minishell *ms, t_token **tokens)
// {
// 	t_token		*t;
// 	t_token		*prev;
// 	t_list		*args;
// 	t_command	*cmd;
// 	t_command	*head;

// 	cmd = alloc_pool(ms, sizeof(*cmd));
// 	head = cmd;
// 	args = NULL;
// 	while (*tokens)
// 	{
// 		t = *tokens;
// 		if (t->pos > 0)
// 			prev = *(tokens - 1);
// 		if (t->type == PIPE)
// 		{
// 			if (t->pos == 0 || (t->pos > 0 && (prev->type == REDIRECTION || prev->type == PIPE)))
// 				return (warning_syntax(ms, t->src));
// 			head->argc = lstsize(args);
// 			head->args = alloc_pool(ms, sizeof(*head->args) * (head->argc + 1));
// 			while (args)
// 			{
// 				*head->args++ = args->content;
// 				args = args->next;
// 			}
// 			head->args -= head->argc;
// 			head->next = alloc_pool(ms, sizeof(*head->next));
// 			head = head->next;
// 			head->redirs = alloc_pool(ms, sizeof(*cmd->redirs));
// 			args = NULL;
// 		}
// 		if (\
// (t->type == REDIRECTION && t->pos > 0 && prev->type == REDIRECTION) || \
// (t->type == NEW_LINE && t->pos > 0 && \
// (prev->type == REDIRECTION || prev->type == PIPE)))
// 			return (warning_syntax(ms, t->src));
// 		if (t->type == WORD)
// 		{
// 			if (t->pos == 0 || (!args && (prev->type == WORD || (prev->pos != 0 && prev->type == PIPE))))
// 				args = lstnew(ms, t->src);
// 			else if (args && prev->type == WORD)
// 				lstadd_back(&args, lstnew(ms, t->src));
// 			else if (prev->type == REDIRECTION)
// 			{
// 				head->redirs = alloc_pool(ms, sizeof(*head->redirs));
// 				if (!ft_strcmp(prev->src, "<"))
// 					head->redirs->type = IN;
// 				else if (!ft_strcmp(prev->src, ">"))
// 					head->redirs->type = OUT;
// 				else if (!ft_strcmp(prev->src, ">>"))
// 					head->redirs->type = OUT_APPEND;
// 				else if (!ft_strcmp(prev->src, "<<"))
// 					head->redirs->type = HEREDOC;
// 				head->redirs->filename = t->src;
// 				head->redirs = head->redirs->next;
// 			}
// 		}
// 		++tokens;
// 	}
// 	if (args)
// 	{
// 		head->argc = lstsize(args);
// 		head->args = alloc_pool(ms, sizeof(*head->args) * (head->argc + 1));
// 		while (args)
// 		{
// 			*head->args++ = args->content;
// 			args = args->next;
// 		}
// 		head->args -= head->argc;
// 	}
// 	return (cmd);
// }

t_command	*parse_tokens(t_minishell *ms, t_token **tokens)
{
	t_token		*t;
	t_token		*prev;
	t_list		*args;
	t_command	*cmd;
	t_command	*head;
	t_redir		*redir;

	cmd = alloc_pool(ms, sizeof(*cmd));
	head = cmd;
	args = NULL;
	while (*tokens)
	{
		t = *tokens;
		if (t->pos > 0)
			prev = *(tokens - 1);
		if (t->type == PIPE)
		{
			if (t->pos == 0 || prev->type != WORD)
				return (warning_syntax(ms, t->src));
			head->argc = lstsize(args);
			head->args = alloc_pool(ms, sizeof(*head->args) * (head->argc + 1));
			while (args)
			{
				*head->args++ = args->content;
				args = args->next;
			}
			head->args -= head->argc;
			head->next = alloc_pool(ms, sizeof(*head->next));
			head = head->next;
			args = NULL;
		}
		if (\
t->pos > 0 && \
((t->type == REDIRECTION && prev->type == REDIRECTION) || \
(t->type == NEW_LINE && prev->type != WORD)))
			return (warning_syntax(ms, t->src));
		if (t->type == WORD)
		{
			if (t->pos > 0 && prev->type == REDIRECTION)
			{
				redir = alloc_pool(ms, sizeof(*redir));
				if (!ft_strcmp(prev->src, "<"))
					redir->type = IN;
				else if (!ft_strcmp(prev->src, ">"))
					redir->type = OUT;
				else if (!ft_strcmp(prev->src, ">>"))
					redir->type = OUT_APPEND;
				else if (!ft_strcmp(prev->src, "<<"))
					redir->type = HEREDOC;
				redir->filename = t->src;
				lstadd_back(&head->redirs, lstnew(ms, redir));
			}
			else
				lstadd_back(&args, lstnew(ms, t->src));
		}
		++tokens;
	}
	if (args)
	{
		head->argc = lstsize(args);
		head->args = alloc_pool(ms, sizeof(*head->args) * (head->argc + 1));
		while (args)
		{
			*head->args++ = args->content;
			args = args->next;
		}
		head->args -= head->argc;
	}
	return (cmd);
}

void	expand_variables(t_command **cmd)
{
	(void)cmd;
}

void	handle_redirections(t_command **cmd)
{
	(void)cmd;
}
