/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:00:08 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/25 08:42:21 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include <macros/status.h>
#include <structs/s_table.h>
#include <structs/s_philosopher.h>

#include <modules/philosophers/philosophers_routine.h>
#include <modules/philosophers/philosophers_utils.h>

/**
 * @brief Sleeps for the given milliseconds.
 */
long	msleep(long ms)
{
	return (usleep(ms * 1000));
}

/**
 * @brief Hold the execution untih the mutex signal is avaliable,
 * then return its value.
 */
t_byte	read_signal_mutex(t_byte *signal, pthread_mutex_t *mutex)
{
	t_byte	res;

	pthread_mutex_lock(mutex);
	res = *signal;
	pthread_mutex_unlock(mutex);
	return (res);
}

/**
 * @brief The philosopher routine. It's ran in a thread.
 */
void	*philosopher_routine(void *data)
{
	t_philosopher	*philo;
	t_byte			*dinner_over;

	philo = (t_philosopher *)data;
	dinner_over = philo->signal;
	while (1)
	{
		if (read_signal_mutex(dinner_over, philo->signal_mutex))
			break ;
		philosopher_eat(data);
		if (read_signal_mutex(dinner_over, philo->signal_mutex))
			break ;
		philosopher_sleep(data);
		if (read_signal_mutex(dinner_over, philo->signal_mutex))
			break ;
	}
	return (NULL);
}

/**
 * @brief Initializes the philosophers of a table,
 * then starts each of them in their own thread.
 *
 * Returns 0 when error, otherwise returns the number of
 * successfully started threads.
 */
int	start_philosophers(t_table *table, int count,
	void *(*philo_routine)(void *))
{
	int				i;
	int				res;
	t_philosopher	*philos;

	philos = table->philosophers;
	if (!philos)
		return (0);
	init_philosophers(philos, table, table->config.philo_count);
	i = 0;
	while (i < count)
	{
		res = pthread_create(&(philos[i].thread_id), NULL,
				philo_routine, philos + i);
		if (res != SUCCESS)
			return (0);
		i++;
	}
	return (i);
}
