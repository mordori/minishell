/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:07:18 by myli-pen          #+#    #+#             */
/*   Updated: 2025/10/04 04:44:37 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static inline char		**expand_args(char **args);
static inline t_list	*expand_redirs(t_list *redirs);

void	expand_variables(t_minishell *ms)
{
	t_node	*head;

	head = ms->node;
	while(head)
	{
		head->cmd.args = expand_args(head->cmd.args);
		head->cmd.redirs = expand_redirs(head->cmd.redirs);
		head = head->next;
	}
}

static inline char	**expand_args(char **raw_args)
{
	char	**args;

	args = raw_args;
	while (raw_args)
	{
		++raw_args;
	}
	return (args);
}

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
