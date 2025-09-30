/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:25:46 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/25 14:32:13 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	ft_export(t_cmd *cmd, t_state *state)
{
	//in bash export sets env variables so they are available for child prcesses and extern programas
	//in pipeline: NEEDS to affect subsequent child processes, but not the parent process.
	//makes a new env variable accessible.
	parse_env_var();
}
