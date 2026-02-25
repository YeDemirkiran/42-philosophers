/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 06:38:59 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/25 06:57:43 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <pthread.h>

/**
 * @brief Returns the current time in milliseconds since the start
 * of the program.
 * @return -1 on error, time in milliseconds otherwise.
 */
long	get_time(void)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	static long				epoch;
	long					current_time;
	long					timestamp;
	struct timeval			tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (pthread_mutex_lock(&mutex) != 0)
		return (-1);
	if (epoch == 0)
		epoch = current_time;
	timestamp = current_time - epoch;
	if (pthread_mutex_unlock(&mutex) != 0)
		return (-1);
	return (timestamp);
}
