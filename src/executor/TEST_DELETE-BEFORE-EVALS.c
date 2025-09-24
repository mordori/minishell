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

int main(void)
{
	char *command_line_echo = "echo hello world";
	char *command_line_pwd = "pwd";
	char *command_line_cd = "cd";
	char **command_line_pipli = {"ls -l", "grep *.c", "wc -l"};

	t_state *shell = malloc(t_state);
	t_node *node = malloc(sizeof(t_node) * 3);
	t_cmd *cmd = malloc(sizeof(t_cmd));

	node->left = cmd1;
	node->next->left = cmd2;
	node->next->next->left = cmd3;

	executor();

	free(shell);
	free(node);
	free(cmd);

}
