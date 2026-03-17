/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:00:08 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 10:20:23 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <stdbool.h>
#include <unistd.h>
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
 */
static void	philosopher_routine(t_philosopher philo)
{
	while (1)
	{
		if (!should_philo_continue(&philo))
		{
			sem_close(philo.forks);
			sem_close(philo.print_semaphore);
			exit(EXIT_FAILURE);
		}
		if (!philosopher_eat(&philo))
		{
			sem_close(philo.forks);
			sem_close(philo.print_semaphore);
			exit(EXIT_FAILURE);
		}
		if (!should_philo_continue(&philo))
		{
			sem_close(philo.forks);
			sem_close(philo.print_semaphore);
			exit(EXIT_FAILURE);
		}
		if (!philosopher_sleep(&philo))
		{
			sem_close(philo.forks);
			sem_close(philo.print_semaphore);
			exit(EXIT_FAILURE);
		}
		if (!should_philo_continue(&philo))
		{
			sem_close(philo.forks);
			sem_close(philo.print_semaphore);
			exit(EXIT_FAILURE);
		}
	}
	
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
			philosopher_routine(philo);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	return (i);
}
