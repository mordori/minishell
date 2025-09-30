/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:41:25 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/25 14:30:26 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// was more efficient to move the intermediate run_node() into cmd_processor.c
//
// but if more specific child_processing is needed afterall, return run_node and resume here.
