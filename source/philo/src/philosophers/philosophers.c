/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:00:08 by yademirk          #+#    #+#             */
/*   Updated: 2025/10/12 20:32:55 by yademirk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include <macros/status.h>
#include <structs/s_table.h>
#include <structs/s_thread_data.h>

#include <modules/philosophers/philosophers_routine.h>
#include <modules/philosophers/philosophers_utils.h>

/**
 * @brief Sleep for ms, then return the time difference since the beginning.
 *
 * The first call returns always 0. To get the current timestamp without
 * sleeping, make ms 0.
 */
long	time_philosopher(t_thread_data *data, long ms)
{
	long			current_time;
	long			timestamp;
	struct timeval	tv;

	if (ms > 0)
		usleep(ms * 1000);
	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (data->time_in_ms == 0)
		data->time_in_ms = current_time;
	timestamp = current_time - data->time_in_ms;
	return (timestamp);
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
	t_thread_data	*thread_data;
	t_byte			*dinner_over;

	thread_data = (t_thread_data *)data;
	dinner_over = thread_data->signal;
	while (1)
	{
		if (!read_signal_mutex(dinner_over, thread_data->signal_mutex))
			break ;
	}
	while (1)
	{
		if (read_signal_mutex(dinner_over, thread_data->signal_mutex))
			break ;
		philosopher_eat(data);
		if (read_signal_mutex(dinner_over, thread_data->signal_mutex))
			break ;
		philosopher_sleep(data);
		if (read_signal_mutex(dinner_over, thread_data->signal_mutex))
			break ;
	}
	free(data);
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
	t_thread_data	**data;

	philos = table->philosophers;
	if (!philos)
		return (0);
	init_philosophers(philos, table->forks, table->config.philo_count);
	data = malloc(sizeof(t_thread_data *) * count);
	if (!data)
		return (0);
	i = 0;
	while (i < count)
	{
		data[i] = malloc(sizeof(t_thread_data));
		data[i]->philosopher = philos + i;
		data[i]->config = &(table->config);
		data[i]->time_in_ms = 0;
		data[i]->last_meal_time = 0;
		data[i]->signal = &(table->dinner_over);
		data[i]->signal_mutex = &(table->over_mutex);
		data[i]->print_mutex = &(table->print_mutex);
		i++;
	}
	i = 0;
	while (i < count)
	{
		res = pthread_create(&(philos[i].thread_id), NULL,
				philo_routine, data[i]);
		if (res != SUCCESS)
		{
			free(data);
			return (0);
		}
		i++;
	}
	free(data);
	pthread_mutex_lock(&table->over_mutex);
	table->dinner_over = 0;
	pthread_mutex_unlock(&table->over_mutex);
	return (i);
}
