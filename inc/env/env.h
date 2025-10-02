/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:17:25 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/01 16:05:59 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include "defines.h"
# include "libft_str.h"
# include "env_utils.h"
# include "mem_utils.h"

int		envp_to_envll(char **envp, t_state *state);
void	var_to_node(char *var, t_env *env);
char	**envll_to_envp(t_env *env);
void	quicksort(char **envp, size_t len);

#endif
