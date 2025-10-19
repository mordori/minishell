/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:17:25 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/17 17:31:58 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include "defines.h"
# include "libft_str.h"
# include "env_utils.h"
# include "arena.h"

int		envp_to_envll(t_minishell *ms, char **envp, t_state *state);
void	var_to_node(t_minishell *ms, char *var, t_env **env);
char	**envll_to_envp(t_minishell *ms, t_env *env);
void	quicksort(t_env *low, t_env *high);

#endif
