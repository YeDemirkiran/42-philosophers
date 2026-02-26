/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:46:31 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/26 15:13:12 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_UTILS_H
# define PHILOSOPHERS_UTILS_H

# include <pthread.h>
# include <structs/s_philosopher.h>

/**
 * @brief This function does two things:
 *
 * 1 - Checks if the philosopher is dead and prints the death message
 *
 * 2 - Checks if the dinner is over
 *
 * @return 0 if the philosopher should stop, 1 if it should continue.
 */
int		should_philo_continue(t_philosopher *philo);
void	init_philosophers(t_philosopher *philos, t_table *table,
			int philo_count);
void	join_philosophers(t_philosopher *philos, int count);

#endif
