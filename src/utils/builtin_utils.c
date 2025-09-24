/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:44:17 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/24 13:59:48 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.h"

bool	is_builtin(t_cmd *command) //the parameter/member format depends on parser output
{
	return (command->builtin_cmd == ECHO
		|| command->builtin_cmd == CD
		|| command->builtin_cmd == PWD
		|| command->builtin_cmd == EXPORT
		|| command->builtin_cmd == UNSET
		|| command->builtin_cmd == ENV
		|| command->builtin_cmd == EXIT);
}
