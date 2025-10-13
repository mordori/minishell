/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:07:18 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/13 12:14:22 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "str_utils.h"
#include "arena_list.h"
#include "arena.h"

static inline char		**expand_args(t_minishell *ms, char **args);
// static inline t_list	*expand_redirs(t_list *redirs);

void	expand_variables(t_minishell *ms)
{
	t_node	*head;

	head = ms->node;
	while(head)
	{
		if (head->cmd.args)
			head->cmd.args = expand_args(ms, head->cmd.args);
		//head->cmd.redirs = expand_redirs(head->cmd.redirs);
		head = head->next;
	}
}

static inline char	**expand_args(t_minishell *ms, char **raw_args)
{
	char	**result;
	char	*start;
	t_list	*args;
	char	*arg;
	int		i;

	args = NULL;
	arg = NULL;
	result = raw_args;
	while (*raw_args)
	{
		start = ft_strchr(*raw_args, '$');
		if (!start) //NO EXPANSION
		{
			lstadd_back(&args, ft_lstnew(*raw_args));
			++raw_args;
			continue ;
		}
		arg = alloc_volatile(ms, sizeof(char) * (start - *raw_args + 1));
		ft_memcpy(arg, *raw_args, start - *raw_args);
		while (start++)
		{
			if (!*start)
				arg = str_join(ms, arg, start - 1);
			if (*start == '?')
			{
				arg = str_join(ms, arg, int_to_str(ms, ms->state.exit_status));
				++start;
			}
			if (*start == '$')
			{
				arg = str_join(ms, arg, int_to_str(ms, getpid()));
				++start;
			}
			if (*start == '\"' || *start == '\'')
			{
				i = start - *raw_args;
				printf("%c\n", start[i]);
				while (start[i] && start[i] != '\"')
					++i;
				printf("%c\n", start[--i]);
				arg = str_join(ms, arg, str_sub(ms, start, start - *raw_args, i));
				start += i + 2;
			}
			else //TRY TO FIND VAR AND EXPAND
			{
				;
				// size_t	i;
				// t_env	*env;

				// i = 0;
				// while (start[i] && start[i] != '$')
				// 	++i;
				// env = find_key(ms->state, str_sub(ms, start, 0, i));
				// if (env)
				// 	lstadd_back(&args, ft_lstnew(env->value));
			}
			if (!ft_strchr(start, '$'))
				break;
			start = ft_strchr(start, '$');
		}
		arg = str_join(ms, arg, start);
		printf("%s\n", arg);
		++raw_args;
	}
	return (result);
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
