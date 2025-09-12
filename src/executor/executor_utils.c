/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:58:00 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/12 15:58:18 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "executor.h"

bool	is_builtin(t_cmd *command) //the parameter/member format depends on parser output
{
	return (command->cmd == ECHO
		|| command->cmd == CD
		|| command->cmd == PWD
		|| command->cmd == EXPORT
		|| command->cmd == UNSET
		|| command->cmd == ENV
		|| command->cmd == EXIT);
}
