/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:37:54 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 12:56:21 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include "structs/s_table.h"
# include "types/t_byte.h"

/**
 * @brief Inits the dinner table.
 *
 * @return 0 on success, 1 on failure.
 */
t_byte	init_table(t_table *table, int argc, char **argv);

/**
 * @brief Clears the dinner table.
 *
 * - Clears and frees all philosophers
 *
 * - Destroys all semaphores
 */
void	clear_table(t_table *table);

#endif
