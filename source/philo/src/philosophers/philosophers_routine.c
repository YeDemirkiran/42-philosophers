/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:35:34 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/16 01:08:42 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "structs/s_philosopher.h"
#include "modules/utils.h"

#include "philosophers_utils.h"

// colors for reference

#define THINK_COLOR "\033[1;93m"
#define TAKE_FORK_COLOR "\033[1;37m"
#define EAT_COLOR "\033[1;92m"
#define SLEEP_COLOR "\033[1;96m"
#define COLOR_RESET "\033[0m"

// We'll have to embed color codes directly in the macro
// Instead of being able to use the defined ones already
// Thanks Norm

#define EAT_MESSAGE "\033[1;92mis eating\033[0m\n"
#define THINK_MESSAGE "\033[1;93mis thinking\033[0m\n"
#define FORK_MESSAGE "\033[1;37mhas taken a fork\033[0m\n"
#define SLEEP_MESSAGE "\033[1;96mis sleeping\033[0m\n"

/**
 * @brief Leaves forks in the order they are acquired.
 */
static void	leave_forks(t_philosopher *philo)
{
	if (philo->left_fork != NULL)
		pthread_mutex_unlock(philo->left_fork);
	if (philo->left_fork != philo->right_fork && philo->right_fork != NULL)
		pthread_mutex_unlock(philo->right_fork);
}

/**
 * @brief Acquires forks in a left-right order.
 *
 * @return 0 on failure (philosopher death, dinner over), 1 on success.
 *
 * @note You should exit the thread when 0 is returned.
 */
static int	take_forks(t_philosopher *philo)
{
	pthread_mutex_t	*first_fork;

	if (!should_philo_continue(philo))
		return (0);
	philo_message(philo->id, THINK_MESSAGE, get_time());
	if (philo->right_fork == NULL)
		first_fork = philo->left_fork;
	else
		first_fork = philo->right_fork;
	pthread_mutex_lock(first_fork);
	if (!should_philo_continue(philo))
	{
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	philo_message(philo->id, FORK_MESSAGE, get_time());
	if (philo->left_fork == philo->right_fork || philo->right_fork == NULL)
	{
		interval_sleep(philo->config->starve_time, philo);
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	if (first_fork == philo->left_fork)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (!should_philo_continue(philo))
	{
		leave_forks(philo);
		return (0);
	}
	philo_message(philo->id, FORK_MESSAGE, get_time());
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
int	philosopher_eat(t_philosopher *philo)
{
	long	last_meal_time;
	size_t	new_eat_count;
	size_t	max_eat_count;

	if (!take_forks(philo))
		return (0);
	last_meal_time = get_time();
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (!should_philo_continue(philo))
	{
		leave_forks(philo);
		return (0);
	}
	philo_message(philo->id, EAT_MESSAGE, last_meal_time);
	interval_sleep(philo->config->eat_time, philo);
	leave_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->eat_count += 1;
	new_eat_count = philo->eat_count;
	max_eat_count = philo->config->eat_count;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (max_eat_count != 0 && new_eat_count >= max_eat_count)
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
int	philosopher_sleep(t_philosopher *philo)
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
	philo_message(philo->id, SLEEP_MESSAGE, time);
	if (interval_sleep(philo->config->sleep_time, philo) != 1)
		return (0);
	return (1);
}
