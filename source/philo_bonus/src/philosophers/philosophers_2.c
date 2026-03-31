/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 11:19:21 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/31 11:21:30 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>

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
			return (philo_clear_and_return(philo, 2));
		if (!philosopher_eat(philo))
			return (philo_clear_and_return(philo, 2));
		if (!should_philo_continue(philo))
			return (philo_clear_and_return(philo, 2));
		if (!philosopher_sleep(philo))
			return (philo_clear_and_return(philo, 2));
		if (!should_philo_continue(philo))
			return (philo_clear_and_return(philo, 2));
	}
	return (philo_clear_and_return(philo, 0));
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
static int	philosopher_monitor(t_philosopher *philo, long starve_time,
	sem_t *meal_sem)
{
	long	time;
	long	last_meal_time;

	while (1)
	{
		time = get_time();
		if (time == -1)
		{
			philo_error("internal: Can't get time (in philosopher_monitor)");
			return (EXIT_FAILURE);
		}
		sem_wait(meal_sem);
		last_meal_time = philo->last_meal_time;
		sem_post(meal_sem);
		if (time - last_meal_time >= starve_time)
			return (2);
		if (usleep(MONITOR_INTERVAL_MS * 1000) != SUCCESS)
		{
			philo_error("internal: Can't sleep (in philosopher_monitor)");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Forms a meal semaphore name with the given
 * ID and creates it.
 * 
 * @return SEM_FAILED on failure, and the semaphore on success.
 */
static sem_t	*create_meal_semaphore(int id)
{
	static char	file_name[23] = "/philo_meal_0000000000";
	int			i;
	sem_t		*sem;

	i = 22;
	while (--i > 11)
		file_name[i] = '0';
	if (id <= 0)
		id = 1;
	i = 21;
	while (id > 0)
	{
		file_name[i] = (id % 10) + '0';
		id /= 10;
		i--;
	}
	sem = create_sem(file_name, 1);
	if (sem == SEM_FAILED)
	{
		philo_error("internal: Can't create philosopher meal semaphore");
		return (SEM_FAILED);
	}
	return (sem);
}

/**
 * @brief Starts both the philosopher thread and the monitor.
 *
 * Automatically exits with a failure code on errors.
 */
void	start_philosopher_and_monitor(t_philosopher *philo)
{
	pthread_t	thread;
	void		*thread_return;
	sem_t		*meal_sem;
	int			starve_time;
	int			result;

	philo->meal_semaphore = NULL;
	meal_sem = create_meal_semaphore(philo->id);
	if (meal_sem == SEM_FAILED)
		philo_clear_and_exit(philo, EXIT_FAILURE);
	starve_time = (long)philo->config->starve_time;
	philo->meal_semaphore = meal_sem;
	result = pthread_create(&thread, NULL, philosopher_routine, (void *)philo);
	if (result != SUCCESS)
	{
		philo_error("internal: Can't start philosopher thread");
		philo_clear_and_exit(philo, EXIT_FAILURE);
	}
	result = philosopher_monitor(philo, starve_time, meal_sem);
	pthread_join(thread, &thread_return);
	if (*(int *)thread_return > result)
		result = *(int *)thread_return;
	free(thread_return);
	sem_close(meal_sem);
	exit(result);
}