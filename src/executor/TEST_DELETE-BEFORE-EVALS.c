/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:09:48 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/22 18:29:00 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "executor.h"
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	//char *command_line_echo = "echo hello world";
	//char *command_line_pwd = "pwd";
	//char *command_line_cd = "cd";
	char **pipli = {"ls -l", "grep *.c", "wc -l"};

	t_minishell *ms = malloc(sizeof(t_minishell));
	t_state *state = malloc(sizeof(t_state));

	t_node *node1 = malloc(sizeof(t_node));
	t_node *node2 = malloc(sizeof(t_node));
	t_node *node3 = malloc(sizeof(t_node));

	t_cmd *cmd1 = malloc(sizeof(t_cmd));
	t_cmd *cmd2 = malloc(sizeof(t_cmd));
	t_cmd *cmd3 = malloc(sizeof(t_cmd));
	cmd1->args = pipli[0];
	cmd2->args = pipli[1];
	cmd3->args = pipli[2];

	node1->prev = NULL;
	node1->next = node2;
	node2->next = node3;
	node2->prev = node1;
	node3->prev = node2;
	node3->next = NULL;

	node1->cmd = cmd1;
	node2->cmd = cmd2;
	node3->cmd = cmd3;

	ms->state = state;
	ms->node = node;

	executor(ms);

	free(cmd);
	free(node);
	free(state);
	free(ms);

	return (0);
}
