/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:31:44 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/12 08:44:44 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include <macros/status.h>
#include <structs/s_philosopher.h>
#include <structs/s_table.h>

#include "modules/utils.h"

/**
 * @brief Hold the execution untih the mutex signal is avaliable,
 * then return its value.
 */
static t_byte	read_signal_mutex(t_byte *signal, pthread_mutex_t *mutex)
{
	t_byte	res;

	pthread_mutex_lock(mutex);
	res = *signal;
	pthread_mutex_unlock(mutex);
	return (res);
}

/**
 * @brief This function does two things:
 *
 * 1 - Checks if the philosopher is dead and prints the death message
 *
 * 2 - Checks if the dinner is over
 *
 * @return 0 if the philosopher should stop, 1 if it should continue.
 */
int	should_philo_continue(t_philosopher *philo)
{
	t_byte	dinner_over;

	dinner_over = read_signal_mutex(philo->signal, philo->signal_mutex);
	if (dinner_over)
		return (0);
	return (1);
}

void	init_philosophers(t_philosopher *philos, t_table *table,
	int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		philos[i].id = i;
		philos[i].eat_count = 0;
		philos[i].last_meal_time = 0;
		philos[i].left_fork = table->forks + i;
		if (philo_count < 2)
			philos[i].right_fork = NULL;
		else
			philos[i].right_fork = table->forks + ((i + 1) % philo_count);
		philos[i].config = &(table->config);
		philos[i].signal = &(table->dinner_over);
		philos[i].signal_mutex = &(table->over_mutex);
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
