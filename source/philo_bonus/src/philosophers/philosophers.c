/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:00:08 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 13:32:39 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "structs/s_table.h"
#include "structs/s_philosopher.h"
#include "modules/utils.h"
#include "macros/status.h"

#include "philosophers_utils.h"
#include "philosophers_routine.h"

#ifndef MONITOR_INTERVAL_MS
# define MONITOR_INTERVAL_MS 2
#endif

/**
 * @brief The philosopher routine. It's used in a thread.
 */
static void	*philosopher_routine(void *data)
{
	t_philosopher	*philo;

	if (data == NULL)
		return (NULL);
	philo = (t_philosopher *)data;
	while (1)
	{
		if (!should_philo_continue(philo))
			philo_clear_and_exit(philo, 2);
		if (!philosopher_eat(philo))
			philo_clear_and_exit(philo, 2);
		if (!should_philo_continue(philo))
			philo_clear_and_exit(philo, 2);
		if (!philosopher_sleep(philo))
			philo_clear_and_exit(philo, 2);
		if (!should_philo_continue(philo))
			philo_clear_and_exit(philo, 2);
	}
	return (NULL);
}

/**
 * @brief Runs in a loop and checks a philosopher's state in each
 * interval.
 *
 * Unlike the mandatory part's monitor, this one checks only for one
 * philosopher and only for death, not eat counts.
 * 
 * It kills the child process by exiting.
 *
 * Sleeps for MONITOR_INTERVAL_MS * 1000 duration before each interval.
 */
static void	philosopher_monitor(t_philosopher *philo)
{
	long	time;

	while (1)
	{
		time = get_time();
		if (time == -1)
		{
			philo_error("internal: Can't get time (in philosopher_monitor)");
			philo_clear_and_exit(philo, EXIT_FAILURE);
		}
		if (time - philo->last_meal_time >= (long)philo->config->starve_time)
			philo_clear_and_exit(philo, 2);
		if (usleep(MONITOR_INTERVAL_MS * 1000) != SUCCESS)
		{
			philo_error("internal: Can't sleep (in philosopher_monitor)");
			philo_clear_and_exit(philo, EXIT_FAILURE);
		}
	}
}

/**
 * @brief Starts both the philosopher thread and the monitor.
 * 
 * Automatically exits with a failure code on errors.
 */
static void	start_philosopher_and_monitor(t_philosopher *philo)
{
	pthread_t	thread;
	int			res;

	res = pthread_create(&thread, NULL, philosopher_routine, (void *)philo);
	if (res != SUCCESS)
	{
		philo_error("internal: Can't start philosopher thread");
		philo_clear_and_exit(philo, EXIT_FAILURE);
	}
	philosopher_monitor(philo);
	pthread_join(thread, NULL);
	philo_clear_and_exit(philo, EXIT_SUCCESS);
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
		philos[i].forks = table->forks;
		philos[i].print_semaphore = table->print_semaphore;
		philos[i].eating_semaphore = table->eating_semaphore;
		philos[i].config = &(table->config);
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
	t_philosopher	*philos;
	t_philosopher	philo;

	philos = table->philosophers;
	if (init_philosophers(philos, table, table->config.philo_count) == 0)
		return (0);
	i = 0;
	while (i < count)
	{
		philos[i].pid = fork();
		if (philos[i].pid == -1)
		{
			philo_error("internal: A philosopher process couldn't start");
			return (0);
		}
		else if (philos[i].pid == 0)
		{
			philo = philos[i];
			free(table->philosophers);
			start_philosopher_and_monitor(&philo);
		}
		i++;
	}
	return (i);
}
