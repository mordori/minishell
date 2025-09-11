/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:33:34 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/10 10:57:47 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"
# include <unistd.h>

enum e_cmd_type
{
	SIMPLE,
	PIPELINE
};

struct s_state
{
	int			pid_count;
	pid_t		*pids;
	int			exit_status; //edellisen exit status: tarvitaan $? komentoon
	char		**env_var; //environment variableille
	//whatever else is required to track globl status fo executions
};

struct s_cmd
{
	e_cmd_type		type;
	char			**argv;
	struct s_cmd	*left; //linked list kaytannossa.
	struct s_cmd	*right;
	int				exit_status;
};

#endif
