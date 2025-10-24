/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:26:59 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/24 16:43:16 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "cleanup.h"
#include "errors.h"
#include "io.h"

int	exi(t_minishell *ms)
{
	int	status;

	try_write_endl(ms, STDOUT_FILENO, "exit");
	status = ms->state.exit_status;
	clean(ms);
	exit(status);
}
