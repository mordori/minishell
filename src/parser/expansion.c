/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:07:18 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/06 16:34:12 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "str_utils.h"
#include "arena_list.h"

static inline char		**expand_args(t_minishell *ms, char **args);
static inline t_list	*expand_redirs(t_list *redirs);

void	expand_variables(t_minishell *ms)
{
	t_node	*head;

	head = ms->node;
	while(head)
	{
		head->cmd.args = expand_args(ms, head->cmd.args);
		head->cmd.redirs = expand_redirs(head->cmd.redirs);
		head = head->next;
	}
}

static inline char	**expand_args(t_minishell *ms, char **raw_args)
{
	char	**result;
	char	*start;
	t_list	*args;

	result = raw_args;
	while (raw_args)
	{
		start = ft_strchr(*raw_args, '$');
		if (!start || **raw_args == '\'') //NO EXPANSION
		{
			lstadd_back(&args, ft_lstnew(*raw_args));
			continue ;
		}
		// WORD UNTIL $
		if (start != *raw_args && *(start - 1) == '\"') //NO WORD SPLITTING
		{
			;
		}
		while (start && ++start)
		{
			if (*start == '?') //PRINT LAST ESCAPE CODE
			{
				;
			}
			if (*start == '$') //PRINT SHELL PID
			{
				lstadd_back(&args, ft_lstnew(int_to_str(ms, getpid())));
			}
			if (*start == '\"' || *start == '\'') //LOCALIZATION AND ANSI-C QUOTING - NOT HANDLED
			{
				;
			}
			else //TRY TO FIND VAR AND EXPAND
			{
				// size_t	i;
				// t_env	*env;

				// i = 0;
				// while (start[i] && start[i] != '$')
				// 	++i;
				// env = find_key(ms->state, str_sub(ms, start, 0, i));
				// if (env)
				// 	lstadd_back(&args, ft_lstnew(env->value));
			}
			if (!*start)
				break ;
			start = ft_strchr(start, '$');
		}
		++raw_args;
	}
	return (result);
}


// READ HEREDOC IN TOO

/**
 * *[expansion][~/Projects/minishell]$ cd ~
[~]$ mkdir playground
[~]$ cd playground
[~/playground]$ mkdir new
[~/playground]$ cd new
[~/playground/new]$ rm ../new
rm: cannot remove '../new': Is a directory
[~/playground/new]$ rm -rf ../new
[~/playground/new]$ pwd
/home/myli-pen/playground/new
 */

static inline t_list	*expand_redirs(t_list *raw_redirs)
{
	t_list	*redirs;
	//t_redir	*r;

	redirs = raw_redirs;
	while (raw_redirs)
	{
		//r = (t_redir *)raw_redirs->content;
		raw_redirs = raw_redirs->next;
	}
	return (redirs);
}
