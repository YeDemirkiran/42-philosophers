/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 14:05:05 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/14 22:04:05 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/s_philosopher.h"

/**
 * @brief Converts the given string to a long integer.
 *
 * Additionally checks an optional sign character at the start of the string.
 *
 * @note You can't safely determine if the given string contains invalid
 * characters since this function simply returns 0 on such cases.
 */
long long	ft_atol(const char *str);

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

/**
 * @brief Prints an error message to the standard error
 * in the "philo: error: [message]" format.
 *
 * @note Prints "philo: error: Unknown error" if msg is NULL.
 */
void		philo_error(const char *msg);

/**
 * @brief Sleeps for ms duration, but does it in intervals.
 * Checks whether the philosopher has died with each interval and exits
 * early.
 */
void		interval_sleep(long ms, t_philosopher *philo);
