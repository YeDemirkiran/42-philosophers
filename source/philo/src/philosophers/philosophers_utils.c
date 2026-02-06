/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:31:44 by yademirk          #+#    #+#             */
/*   Updated: 2025/10/15 01:19:45 by yademirk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include <macros/status.h>
#include <structs/s_philosopher.h>
#include <structs/s_thread_data.h>

t_byte	should_philosopher_die(t_thread_data *data, long current_time)
{
	// printf("(%i current time: %li, last meal: %li, starve_time: %lu)\n", *data->philosopher->id, current_time, data->last_meal_time, data->config->starve_time);
	fflush(stdout);
	return (current_time
		>= data->last_meal_time + (long)(data->config->starve_time));
}

void	init_philosophers(t_philosopher *philos, pthread_mutex_t *forks,
	int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		philos[i].id = malloc(sizeof(int));
		*(philos[i].id) = i;
		philos[i].eat_count = 0;
		philos[i].left_fork = forks + i;
		philos[i].right_fork = forks + ((i + 1) % philo_count);
		i++;
	}
}

void	join_philosophers(t_philosopher *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
}

void	free_philosophers(t_philosopher *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(philos[i].id);
		i++;
	}
	free(philos);
}

void	printf_philosopher(pthread_mutex_t *mutex,
	long timestamp, int philo_id, char *string)
{
	pthread_mutex_lock(mutex);
	printf("%li %i %s", timestamp, philo_id, string);
	pthread_mutex_unlock(mutex);
}
