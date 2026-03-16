/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:31:44 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/16 07:31:51 by yademirk         ###   ########.fr       */
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
t_byte	should_philo_continue(t_philosopher *philo)
{
	t_byte	dinner_over;

	if (pthread_mutex_lock(philo->signal_mutex) != SUCCESS)
	{
		philo_error("internal: Can't lock dinner_over mutex");
		return (0);
	}
	dinner_over = *(philo->signal);
	if (pthread_mutex_unlock(philo->signal_mutex) != SUCCESS)
	{
		philo_error("internal: Can't unlock dinner_over mutex");
		return (0);
	}
	return (!dinner_over);
}

/**
 * @brief Iterates over all philosophers and destroys them.
 *
 * - Mutexes are destroyed
 *
 * - The array is free'd
 */
void	clear_philosophers(t_philosopher *philosophers, size_t count)
{
	size_t	i;

	if (philosophers == NULL || count == 0)
		return ;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philosophers[i].meal_mutex);
		i++;
	}
	free(philosophers);
}

/**
 * @brief Initializes all philosopher structs.
 * @return 1 on success, 0 on failure.
 */
int	init_philosophers(t_philosopher *philos, t_table *table,
	size_t philo_count)
{
	size_t	i;

	if (philos == NULL || table == NULL || philo_count == 0)
		return (0);
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
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL) != SUCCESS)
		{
			clear_philosophers(philos, i);
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * @brief Calls pthread_join on all philosophers.
 */
void	join_philosophers(t_philosopher *philos, size_t count)
{
	size_t	i;

	if (philos == NULL || count == 0)
		return ;
	i = 0;
	while (i < count)
	{
		if (pthread_join(philos[i].thread_id, NULL) != SUCCESS)
		{
			philo_error("internal: Can't join one or more threads");
			return ;
		}
		i++;
	}
}
