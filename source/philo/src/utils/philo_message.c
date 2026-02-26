/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 21:25:01 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/26 15:28:10 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

#include "modules/utils.h"

/**
 * @brief Takes a message and prints it in the "philo_id timestamp message"
 * format. Acquires the print lock before doing it, and automatically unlocks
 * the mutex after printing.
 *
 * If parameter optional_time is negative, it
 * automatically retrieves the current time.
 *
 * @return -1 on error (mutex_lock or mutex_unlock fails), and whatever printf
 * returns otherwise.
 */
int	philo_message(int philo_id, const char *message, long optional_time)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	long					timestamp;
	int						result;

	if (optional_time < 0)
	{
		timestamp = get_time();
		if (timestamp == -1)
			return (-1);
	}
	else
		timestamp = optional_time;
	if (pthread_mutex_lock(&mutex) != 0)
		return (-1);
	result = printf("%li %i %s", timestamp, philo_id + 1, message);
	if (pthread_mutex_unlock(&mutex) != 0)
		return (-1);
	return (result);
}
