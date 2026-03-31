/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_2.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 11:20:14 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/31 11:20:56 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_2_H
# define PHILOSOPHERS_2_H

# include "structs/s_philosopher.h"

/**
 * @brief Starts both the philosopher thread and the monitor.
 *
 * Automatically exits with a failure code on errors.
 */
void	start_philosopher_and_monitor(t_philosopher *philo);

#endif