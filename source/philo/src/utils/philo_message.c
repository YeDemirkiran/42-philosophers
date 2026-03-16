/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 21:25:01 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/16 07:27:33 by yademirk         ###   ########.fr       */
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
 * @return -1 on error (mutex_lock or mutex_unlock fails), and whatever printf
 * returns otherwise.
 */
int	philo_message(int philo_id, const char *message, long timestamp)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	int						result;

	if (pthread_mutex_lock(&mutex) != 0)
	{
		philo_error("internal: Can't lock philosopher message mutex");
		return (-1);
	}
	result = printf("%li %i %s", timestamp, philo_id + 1, message);
	if (pthread_mutex_unlock(&mutex) != 0)
	{
		philo_error("internal: Can't unlock philosopher message mutex");
		return (-1);
	}
	return (result);
}
