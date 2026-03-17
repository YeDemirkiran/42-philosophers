/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:35:34 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 10:58:39 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <unistd.h>

#include "structs/s_philosopher.h"
#include "modules/utils.h"
#include "macros/status.h"

#include "philosophers_utils.h"

#include "philo_messages.h"

/**
 * @brief Leaves forks in the order they are acquired.
 *
 * @return 0 on failure, 1 on success.
 */
static t_byte	leave_forks(t_philosopher *philo)
{
	if (philo == NULL)
		return (0);
	if (sem_post(philo->forks) != SUCCESS)
	{
		philo_error("internal: A philosopher couldn't leave its fork");
		return (0);
	}
	if (sem_post(philo->forks) != SUCCESS)
	{
		philo_error("internal: A philosopher couldn't leave its fork");
		return (0);
	}
	return (1);
}

/**
 * @brief Updates the last_meal_time property of a philosopher.
 *
 * @return The last meal time on success, -1 on error.
 */
static long	update_last_meal_time(t_philosopher *philo)
{

	if (philo == NULL)
		return (-1);
	philo->last_meal_time = get_time();
	if (philo->last_meal_time == -1)
	{
		philo_error("internal: Error during last_meal_time update");
		return (-1);
	}
	if (!should_philo_continue(philo))
	{
		leave_forks(philo);
		return (-1);
	}
	return (philo->last_meal_time);
}

/**
 * @brief Increases the eat count property of the philosopher.
 *
 * It also checks if the philosopher has eaten enough and automatically 
 * exits with 0 in such case.
 *
 * @return 0 on either failure or dinner over, 1 on success.
 */
static void	increase_eat_count(t_philosopher *philo)
{
	size_t	new_eat_count;
	size_t	max_eat_count;

	philo->eat_count += 1;
	new_eat_count = philo->eat_count;
	max_eat_count = philo->config->eat_count;
	if (max_eat_count != 0 && new_eat_count >= max_eat_count)
	{
		sem_close(philo->forks);
		sem_close(philo->print_semaphore);
		exit(EXIT_SUCCESS);
	}
}

/**
 * @brief Acquires the forks automatically and starts eating.
 *
 * Checks the death and dinner state before each important state
 * and self-terminates accordingly. Returns 0 on such cases, which means
 * the philosopher should stop and exit immediately.
 *
 * @return 0 on failure (death, dinner over), 1 on success.
 */
t_byte	philosopher_eat(t_philosopher *philo)
{
	long	last_meal_time;

	if (sem_wait(philo->eating_semaphore) != SUCCESS || take_forks(philo) != 1)
		return (0);
	last_meal_time = update_last_meal_time(philo);
	if (last_meal_time < 0)
	{
		leave_forks(philo);
		return (0);
	}
	if (philo_message(philo, EAT_MESSAGE, last_meal_time) == -1)
	{
		leave_forks(philo);
		return (0);
	}
	if (interval_sleep(philo->config->eat_time, philo) != 1)
	{
		leave_forks(philo);
		return (0);
	}
	if (leave_forks(philo) != 1)
		return (0);
	increase_eat_count(philo);
	sem_post(philo->eating_semaphore);
	return (1);
}

/**
 * @brief Philosopher sleep routine. Sleeps with intervals.
 * Automatically stops if the philosopher has died or when the
 * dinner is over.
 *
 * @return 0 on failure, 1 on success.
 */
t_byte	philosopher_sleep(t_philosopher *philo)
{
	long	time;

	if (philo == NULL)
		return (0);
	if (!should_philo_continue(philo))
		return (0);
	time = get_time();
	if (time == -1)
	{
		philo_error("internal: A philospher couldn't read time during sleep");
		return (0);
	}
	if (philo_message(philo, SLEEP_MESSAGE, time) == -1)
		return (0);
	if (interval_sleep(philo->config->sleep_time, philo) != 1)
		return (0);
	return (1);
}
