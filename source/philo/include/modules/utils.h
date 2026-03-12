/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 14:05:05 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/12 16:45:02 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/s_philosopher.h"

/**
 * @brief Sleeps for ms duration, but does it in intervals.
 * Checks whether the philosopher has died with each interval and exits
 * early.
 */
void		interval_sleep(long ms, t_philosopher *philo);

/**
 * @brief Returns the current time in milliseconds since the start
 * of the program.
 * @return -1 on error, time in milliseconds otherwise.
 * @note Call once in the main thread to initialize epoch. Otherwise,
 * race conditions may occur.
 */
long		get_time(void);

/**
 * @brief Takes a message and prints it in the "philo_id timestamp message"
 * format. Acquires the print lock before doing it, and automatically unlocks
 * the mutex after printing.
 *
 * @return -1 on error (mutex_lock or mutex_unlock fails), and whatever printf
 * returns otherwise.
 */
int			philo_message(int philo_id, const char *message,
				long timestamp);

long long	ft_atol(char *str);
