/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 21:25:01 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/20 21:36:42 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

/**
 * @brief Takes a message and prints it in the "timestamp philo_id message"
 * format. Acquires the print lock before doing it, and automatically unlocks
 * the mutex after printing.
 *
 * @return Error if mutex_lock or mutex_unlock fails, and whatever printf
 * returns otherwise.
 */
int	philo_message(int philo_id, long timestamp, const char *message)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	int						result;

	if (pthread_mutex_lock(&mutex) != 0)
		return (0);
	result = printf("%li %i %s", timestamp, philo_id, message);
	if (pthread_mutex_unlock(&mutex) != 0)
		return (0);
	return (result);
}
