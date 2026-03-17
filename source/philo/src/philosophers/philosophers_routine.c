/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:35:34 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 08:22:33 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <stdio.h>
#include <pthread.h>
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
	if (philo->left_fork != NULL)
	{
		if (pthread_mutex_unlock(philo->left_fork) != SUCCESS)
		{
			philo_error("internal: A philosopher can't leave its left fork");
			return (0);
		}
	}
	if (philo->left_fork != philo->right_fork && philo->right_fork != NULL)
	{
		if (pthread_mutex_unlock(philo->right_fork) != SUCCESS)
		{
			philo_error("internal: A philosopher can't leave its right fork");
			return (0);
		}
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
	long	last_meal_time;

	last_meal_time = get_time();
	if (last_meal_time == -1)
	{
		philo_error("internal: Error during last_meal_time update");
		return (-1);
	}
	if (pthread_mutex_lock(&philo->meal_mutex) != SUCCESS)
	{
		philo_error("internal: Can't lock meal_mutex during eating");
		return (-1);
	}
	philo->last_meal_time = last_meal_time;
	if (pthread_mutex_unlock(&philo->meal_mutex) != SUCCESS)
	{
		philo_error("internal: Can't unlock meal_mutex during eating");
		return (-1);
	}
	if (!should_philo_continue(philo))
	{
		leave_forks(philo);
		return (-1);
	}
	return (last_meal_time);
}

/**
 * @brief Increases the eat count property of the philosopher.
 *
 * It also checks if the philosopher has eaten enough and returns 0 in such
 * case.
 *
 * @return 0 on either failure or dinner over, 1 on success.
 */
static t_byte	increase_eat_count(t_philosopher *philo)
{
	size_t	new_eat_count;
	size_t	max_eat_count;

	if (pthread_mutex_lock(&philo->meal_mutex) != SUCCESS)
	{
		philo_error("internal: Can't lock meal_mutex during eating");
		return (0);
	}
	philo->eat_count += 1;
	new_eat_count = philo->eat_count;
	max_eat_count = philo->config->eat_count;
	if (pthread_mutex_unlock(&philo->meal_mutex) != SUCCESS)
	{
		philo_error("internal: Can't unlock meal_mutex during eating");
		return (0);
	}
	if (max_eat_count != 0 && new_eat_count >= max_eat_count)
		return (0);
	return (1);
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

	if (philo == NULL || !take_forks(philo, philo->config->starve_time))
		return (0);
	last_meal_time = update_last_meal_time(philo);
	if (last_meal_time < 0)
	{
		leave_forks(philo);
		return (0);
	}
	if (philo_message(philo->id, EAT_MESSAGE, last_meal_time) == -1)
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
	if (increase_eat_count(philo) != 1)
		return (0);
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
	if (philo_message(philo->id, SLEEP_MESSAGE, time) == -1)
		return (0);
	if (interval_sleep(philo->config->sleep_time, philo) != 1)
		return (0);
	return (1);
}
