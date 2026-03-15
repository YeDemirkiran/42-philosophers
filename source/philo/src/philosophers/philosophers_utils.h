/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:46:31 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/15 22:50:33 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_UTILS_H
# define PHILOSOPHERS_UTILS_H

# include <pthread.h>
# include <structs/s_table.h>

/**
 * @return 0 if the philosopher should stop, 1 if it should continue.
 */
int		should_philo_continue(t_philosopher *philo);

/**
 * @brief Initializes all philosopher structs.
 * @return 1 on success, 0 on failure.
 */
int		init_philosophers(t_philosopher *philos, t_table *table,
			size_t philo_count);

/**
 * @brief Calls pthread_join on all philosophers.
 */
void	join_philosophers(t_philosopher *philos, int count);

#endif
