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
# define CMD_ERROR_NOTFOUND		127
# define CMD_ERROR_CANNOTEX		126
# define ERROR					-1
# define SUCCESS				0

typedef struct s_state			t_state;
typedef struct s_cmd			t_cmd;
typedef enum e_cmd_type			t_cmd_type;

#endif
