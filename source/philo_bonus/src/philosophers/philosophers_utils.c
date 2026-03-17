/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:31:44 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 13:00:37 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdlib.h>

#include "macros/status.h"
#include "structs/s_philosopher.h"
#include "structs/s_table.h"

#include "modules/utils.h"

#include "philo_messages.h"

void	philo_clear_and_exit(t_philosopher *philo, int status)
{
	sem_close(philo->forks);
	sem_close(philo->print_semaphore);
	sem_close(philo->eating_semaphore);
	exit(status);
}

/**
 * @return 0 if the philosopher should stop, 1 if it should continue.
 */
t_byte	should_philo_continue(t_philosopher *philo)
{
	long	time;

	time = get_time();
	if (time == -1)
	{
		philo_error("internal: Can't get time (in should_philo_continue)");
		return (0);
	}
	if (time - philo->last_meal_time >= (long)philo->config->starve_time)
		return (0);
	return (1);
}

/**
 * @brief Takes a fork and prints a message.
 *
 * @return 0 on failure, 1 on success.
 */
static t_byte	take_fork(t_philosopher *philo)
{
	if (philo == NULL)
		return (0);
	if (sem_wait(philo->forks) != SUCCESS)
	{
		philo_error("internal: Can't take fork (semaphore error)");
		return (0);
	}
	if (!should_philo_continue(philo))
	{
		sem_post(philo->forks);
		return (0);
	}
	if (philo_message(philo, FORK_MESSAGE, get_time()) == -1)
	{
		sem_post(philo->forks);
		return (0);
	}
	return (1);
}

/**
 * @brief Acquires forks from the center of the table.
 *
 * @return 0 on failure (philosopher death, dinner over), 1 on success.
 *
 * @note You should exit the thread when 0 is returned.
 */
t_byte	take_forks(t_philosopher *philo)
{
	if (!should_philo_continue(philo))
		return (0);
	if (philo_message(philo, THINK_MESSAGE, get_time()) == -1)
		return (0);
	usleep((philo->last_meal_time + philo->config->starve_time - get_time())
		* 10);
	if (take_fork(philo) != 1)
		return (0);
	if (philo->config->philo_count == 1)
	{
		interval_sleep(philo->config->starve_time, philo);
		sem_post(philo->forks);
		return (0);
	}
	if (take_fork(philo) != 1)
		return (0);
	return (1);
}
