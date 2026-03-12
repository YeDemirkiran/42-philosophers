/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:35:34 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/12 16:46:52 by yademirk         ###   ########.fr       */
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

static void	leave_forks(t_philosopher *philo)
{
	if (philo->left_fork != NULL)
		pthread_mutex_unlock(philo->left_fork);
	if (philo->left_fork != philo->right_fork && philo->right_fork != NULL)
		pthread_mutex_unlock(philo->right_fork);
}

static int	take_forks(t_philosopher *philo)
{
	pthread_mutex_t	*first_fork;

	if (!should_philo_continue(philo))
		return (0);
	philo_message(philo->id, THINK_MESSAGE, get_time());
	if (philo->left_fork < philo->right_fork || philo->right_fork == NULL)
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

int	philosopher_eat(t_philosopher *philo)
{
	long	last_meal_time;

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
	pthread_mutex_unlock(&philo->meal_mutex);
	return (1);
}

void	philosopher_sleep(t_philosopher *philo)
{
	long	time;

	if (!should_philo_continue(philo))
		return ;
	time = get_time();
	philo_message(philo->id, SLEEP_MESSAGE, time);
	interval_sleep(philo->config->sleep_time, philo);
}
