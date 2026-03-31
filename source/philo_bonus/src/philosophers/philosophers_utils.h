/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:46:31 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/31 11:24:28 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_UTILS_H
# define PHILOSOPHERS_UTILS_H

# include "structs/s_philosopher.h"
# include "types/t_byte.h"

/**
 * @brief Cleans up the philosopher resources and exits.
 * 
 * Cleaned resources are:
 * 
 * - Forks semaphore
 * - Print semaphore
 * - Eating semaphore
 */
void	philo_clear_and_exit(t_philosopher *philo, int status);

/**
 * @brief Closes all philosopher semaphores and returns
 * the status code in malloc'd pointer.
 * 
 * @return NULL on failure.
 */
int		*philo_clear_and_return(t_philosopher *philo, int status);

/**
 * @return 0 if the philosopher should stop, 1 if it should continue.
 */
t_byte	should_philo_continue(t_philosopher *philo);

/**
 * @brief Acquires forks from the center of the table.
 *
 * @return 0 on failure (philosopher death, dinner over), 1 on success.
 *
 * @note You should exit the thread when 0 is returned.
 */
t_byte	take_forks(t_philosopher *philo);

#endif
