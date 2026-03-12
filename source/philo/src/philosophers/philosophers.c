/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:00:08 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/12 15:47:45 by yademirk         ###   ########.fr       */
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
#include "structs/s_table.h"
#include "structs/s_philosopher.h"

#include "philosophers_utils.h"
#include "philosophers_routine.h"

/**
 * @brief The philosopher routine. It's ran in a thread.
 */
void	*philosopher_routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (!should_philo_continue(philo))
			break ;
		if (!philosopher_eat(data))
			break ;
		if (!should_philo_continue(philo))
			break ;
		philosopher_sleep(data);
		if (!should_philo_continue(philo))
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
int	start_philosophers(t_table *table, int count)
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
				philosopher_routine, philos + i);
		if (res != SUCCESS)
			return (0);
		i++;
	}
	return (i);
}
