/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:00:08 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 09:37:10 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "macros/status.h"
#include "modules/utils.h"
#include "structs/s_table.h"
#include "structs/s_philosopher.h"

#include "philosophers_utils.h"
#include "philosophers_routine.h"

/**
 * @brief The philosopher routine. It's used in a thread.
 *
 * @return NULL.
 */
static void	*philosopher_routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	while (1)
	{
		if (!should_philo_continue(philo))
			break ;
		if (!philosopher_eat(philo))
			break ;
		if (!should_philo_continue(philo))
			break ;
		if (!philosopher_sleep(philo))
			break ;
		if (!should_philo_continue(philo))
			break ;
	}
	return (NULL);
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
static t_byte	init_philosophers(t_philosopher *philos, t_table *table,
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
		philos[i].right_fork = NULL;
		if (philo_count > 1)
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
 * @brief Initializes the philosophers of a table,
 * then starts each of them in their own thread.
 *
 * @return 0 on error, otherwise returns the number of
 * successfully started threads.
 */
size_t	start_philosophers(t_table *table, size_t count)
{
	size_t			i;
	int				res;
	t_philosopher	*philos;

	if (table == NULL || count == 0)
		return (0);
	philos = table->philosophers;
	if (!philos)
		return (0);
	if (init_philosophers(philos, table, table->config.philo_count) == 0)
		return (0);
	i = 0;
	while (i < count)
	{
		res = pthread_create(&(philos[i].thread_id), NULL,
				philosopher_routine, philos + i);
		if (res != SUCCESS)
			return (i);
		i++;
	}
	return (i);
}
