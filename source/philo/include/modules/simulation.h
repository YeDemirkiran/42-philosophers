/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:39:10 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 12:40:32 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "structs/s_table.h"

/**
 * @brief Starts the dinner simulation and the monitor.
 *
 * The monitor keeps checking every philosopher in an interval.
 * When a philosopher dies or all philosophers has eaten enough, the
 * simulation stops.
 */
void	start_simulation(t_table *table);

#endif
