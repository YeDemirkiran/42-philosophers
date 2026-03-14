/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:31:44 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/14 21:20:29 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include <macros/status.h>
#include <structs/s_philosopher.h>
#include <structs/s_table.h>

#include "modules/utils.h"

/**
 * @return 0 if the philosopher should stop, 1 if it should continue.
 */
int	should_philo_continue(t_philosopher *philo)
{
	t_byte	dinner_over;

	pthread_mutex_lock(philo->signal_mutex);
	dinner_over = *(philo->signal);
	pthread_mutex_unlock(philo->signal_mutex);
	if (dinner_over)
		return (0);
	return (1);
}

/**
 * @brief Initializes all philosopher structs.
 * @return 1 on success, 0 on failure.
 */
int	init_philosophers(t_philosopher *philos, t_table *table,
	int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		philos[i].id = i;
		philos[i].eat_count = 0;
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
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
	return (1);
}

/**
 * @brief Calls pthread_join on all philosophers.
 */
void	join_philosophers(t_philosopher *philos, int count)
{
	int	i;

	if (philos == NULL || count <= 0)
		return ;
	i = 0;
	while (i < count)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
}
