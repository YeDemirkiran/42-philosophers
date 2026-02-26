/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 14:05:05 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/26 15:11:10 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Sleeps for the given milliseconds.
 */
long		msleep(long ms);

/**
 * @brief Returns the current time in milliseconds since the start
 * of the program.
 * @return -1 on error, time in milliseconds otherwise.
 */
long		get_time(void);

/**
 * @brief Takes a message and prints it in the "philo_id timestamp message"
 * format. Acquires the print lock before doing it, and automatically unlocks
 * the mutex after printing.
 *
 * It automatically retrieves the current time.
 *
 * @return -1 on error (mutex_lock or mutex_unlock fails), and whatever printf
 * returns otherwise.
 */
int			philo_message(int philo_id, const char *message,
				long optional_time);

long long	ft_atol(char *str);
