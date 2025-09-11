/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:55:02 by myli-pen          #+#    #+#             */
/*   Updated: 2025/09/02 16:55:47 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <stdbool.h>
# include <stdint.h>
# include <sys/types.h>
# include <stddef.h>
# include <limits.h>

// 127 and 126 on bash error codeja, cmd not found, ja cannot execute
// bashissa 126 cannot-execute triggeroityy yleensa jos bad permissions tai shebang puuttuu
# define ERROR_CMD_NOTFOUND		127
# define ERROR_CMD_CANTEXEC		126
# define ERROR					-1
# define SUCCESS				0

typedef struct s_state
{
	int			pid_count;
	pid_t		*pids;
	int			exit_status; //edellisen exit status: tarvitaan $? komentoon
	char		**env_var; //environment variableille
	//whatever else is required to track globl status fo executions
}	t_state;

typedef struct s_cmd
{
	e_cmd_type		type;
	char			**argv; //MIKA we can change this memb if parser refines args to data.
	struct s_cmd	*left; //linked list kaytannossa.
	struct s_cmd	*right;
	int				exit_status;
}	t_cmd;

typedef enum e_cmd_type
{
	SIMPLE,
	PIPELINE
}	t_cmd_type;

typedef enum e_builtin_type
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtin;

#endif
