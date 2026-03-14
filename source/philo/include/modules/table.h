/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:37:54 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/14 20:22:51 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include <structs/s_table.h>

/**
 * @brief Inits the dinner table.
 *
 * @return 0 on success, 1 on failure.
 */
int		init_table(t_table *table, int argc, char **argv);

/**
 * @brief Clears the dinner table.
 *
 * - Clears and frees all philosophers
 *
 * - Destroys all mutexes
 */
void	clear_table(t_table *table);

#endif
