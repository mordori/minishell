/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 05:06:20 by myli-pen          #+#    #+#             */
/*   Updated: 2025/11/18 02:48:45 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "libft_str.h"
#include "errors.h"

void	dup_redirections(t_minishell *ms, t_node *node)
{
	if (node->cmd.redir_in != STDIN_FILENO && node->cmd.redir_in != ERROR)
	{
		if (dup2(node->cmd.redir_in, STDIN_FILENO) == ERROR)
			error_exit(ms, "dup2 redir in failed");
		close (node->cmd.redir_in);
	}
	if (node->cmd.redir_out != STDOUT_FILENO && node->cmd.redir_out != ERROR)
	{
		if (dup2(node->cmd.redir_out, STDOUT_FILENO) == ERROR)
			error_exit(ms, "dup2 redir out failed");
		close (node->cmd.redir_out);
	}
}
