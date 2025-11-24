/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:25:46 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/24 14:53:04 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_utils.h"

static void	display_vars(t_minishell *ms, t_state *state);
static void	put_vars_into_env(t_minishell *ms, t_node *node);

int	expo(t_minishell *ms, t_node *node)
{
	if (!node->cmd.args[1])
		display_vars(ms, &ms->state);
	else
	{
		copy_env_to(VOLATILE, ms);
		arena_reset(&ms->vars);
		put_vars_into_env(ms, node);
		copy_env_to(PERSISTENT, ms);
	}
	if (ms->state.exit_status == ERROR_GENERAL)
		return (ERROR_GENERAL);
	return (SUCCESS);
}

static void	display_vars(t_minishell *ms, t_state *state)
{
	t_env		*head;
	t_env		*last;
	int			fd_out;

	fd_out = STDOUT_FILENO;
	if (ms->state.mode == SIMPLE)
		fd_out = ms->node->cmd.redir_out;
	head = state->env;
	last = envlast(state->env);
	quicksort(head, last);
	while (head)
	{
		if (head->value)
		{
			try_write_endl(ms, fd_out, str_join(ms, \
"declare -x ", str_join(ms, \
head->key, str_join(ms, \
"=\"", str_join(ms, \
head->value, "\"", VOLATILE), VOLATILE), VOLATILE), VOLATILE));
		}
		else
		{
			try_write_endl(ms, fd_out, str_join(ms, \
"declare -x ", head->key, VOLATILE));
		}
		head = head->next;
	}
}

static void	put_vars_into_env(t_minishell *ms, t_node *node)
{
	int				i;
	t_env			*env;
	t_key_value		kv;

	i = 1;
	env = ms->state.env;
	while (i < node->cmd.argc)
	{
		if (handle_cases(ms, i, env, &kv) == false)
		{
			ft_envadd_back(&env, \
ft_envnode_new(ms, kv.k, kv.value, VOLATILE));
		}
		i++;
	}
	ms->state.envp = envll_to_envp(ms, env);
}
