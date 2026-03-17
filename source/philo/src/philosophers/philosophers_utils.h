/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:46:31 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 08:22:29 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_UTILS_H
# define PHILOSOPHERS_UTILS_H

# include <pthread.h>
# include <structs/s_table.h>

/**
 * @return 0 if the philosopher should stop, 1 if it should continue.
 */
t_byte	should_philo_continue(t_philosopher *philo);

/**
 * @brief Acquires forks in a left-right order.
 *
 * @return 0 on failure (philosopher death, dinner over), 1 on success.
 *
 * @note You should exit the thread when 0 is returned.
 */
t_byte	take_forks(t_philosopher *philo, long starve_time);

#endif
