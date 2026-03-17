/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:31:44 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 12:46:04 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <unistd.h>
#include <pthread.h>

#include "macros/status.h"
#include "structs/s_philosopher.h"

#include "modules/utils.h"

#include "philo_messages.h"

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

/**
 * @brief Takes a fork and prints a message.
 *
 * @return 0 on failure, 1 on success.
 */
static t_byte	take_fork(t_philosopher *philo, pthread_mutex_t *fork)
{
	if (philo == NULL || fork == NULL)
		return (0);
	if (pthread_mutex_lock(fork) != SUCCESS)
	{
		philo_error("internal: A philosopher can't take its fork (mutex err)");
		return (0);
	}
	if (!should_philo_continue(philo))
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	if (philo_message(philo->id, FORK_MESSAGE, get_time()) == -1)
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	return (1);
}

/**
 * @brief Chooses a fork out of two based on certain circumstances.
 *
 * If current_fork is NULL, then the lower numbered fork is returned.
 *
 * Else, the opposite of the current_fork is returned.
 */
static pthread_mutex_t	*choose_fork(t_philosopher *philo,
	pthread_mutex_t *current_fork)
{
	pthread_mutex_t	*fork;

	if (philo == NULL)
		return (NULL);
	if (current_fork == NULL)
	{
		if (philo->left_fork < philo->right_fork)
			fork = philo->left_fork;
		else
			fork = philo->right_fork;
	}
	else
	{
		if (current_fork == philo->left_fork)
			fork = philo->right_fork;
		else
			fork = philo->left_fork;
	}
	return (fork);
}

/**
 * @brief Acquires forks in a left-right order.
 *
 * @return 0 on failure (philosopher death, dinner over), 1 on success.
 *
 * @note You should exit the thread when 0 is returned.
 */
t_byte	take_forks(t_philosopher *philo, long starve_time)
{
	long	time;

	if (!should_philo_continue(philo))
		return (0);
	if (philo_message(philo->id, THINK_MESSAGE, get_time()) == -1)
		return (0);
	time = get_time();
	if (time == -1)
		return (0);
	else if (time > 100 && time - philo->last_meal_time < starve_time * 9 / 10)
		usleep((philo->last_meal_time + starve_time - time) * 10);
	if (take_fork(philo, choose_fork(philo, NULL)) != 1)
		return (0);
	if (philo->left_fork == philo->right_fork || philo->right_fork == NULL)
	{
		interval_sleep(philo->config->starve_time, philo);
		pthread_mutex_unlock(choose_fork(philo, NULL));
		return (0);
	}
	if (take_fork(philo, choose_fork(philo, choose_fork(philo, NULL))) != 1)
	{
		pthread_mutex_unlock(choose_fork(philo, choose_fork(philo, NULL)));
		return (0);
	}
	return (1);
}
