/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:35:34 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/25 08:08:40 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

#include "structs/s_philosopher.h"
#include "modules/utils.h"
#include "modules/philosophers/philosophers.h"
#include "modules/philosophers/philosophers_utils.h"

// colors
#define THINK_COLOR "\033[1;93m"
#define TAKE_FORK_COLOR "\033[1;37m"
#define EAT_COLOR "\033[1;92m"
#define SLEEP_COLOR "\033[1;96m"
#define DEATH_COLOR "\033[1;91m"
#define COLOR_RESET "\033[0m"

void	philosopher_die(t_philosopher *philo)
{
	philo_message(philo->id, DEATH_COLOR "died" COLOR_RESET "\n");
	pthread_mutex_lock(philo->signal_mutex);
	if (*philo->signal == 1)
	{
		pthread_mutex_unlock(philo->signal_mutex);
		return ;
	}
	*(philo->signal) = 1;
	pthread_mutex_unlock(philo->signal_mutex);
}

static void	leave_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	if (philo->left_fork == philo->right_fork)
		return ;
	pthread_mutex_unlock(philo->right_fork);
}

static int	take_forks(t_philosopher *philo)
{
	pthread_mutex_t	*first_fork;

	if (read_signal_mutex(philo->signal, philo->signal_mutex))
		return (1);
	if (should_philosopher_die(philo))
	{
		philosopher_die(philo);
		return (0);
	}
	philo_message(philo->id, THINK_COLOR "is thinking" COLOR_RESET "\n");
	if (philo->left_fork < philo->right_fork)
		first_fork = philo->left_fork;
	else
		first_fork = philo->right_fork;
	pthread_mutex_lock(first_fork);
	if (should_philosopher_die(philo))
	{
		philosopher_die(philo);
		return (0);
	}
	if (read_signal_mutex(philo->signal, philo->signal_mutex))
	{
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	philo_message(philo->id, TAKE_FORK_COLOR "has taken a fork" COLOR_RESET "\n");
	if (philo->left_fork == philo->right_fork)
	{
		msleep(philo->config->starve_time);
		pthread_mutex_unlock(first_fork);
		philosopher_die(philo);
		return (0);
	}
	if (first_fork == philo->left_fork)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (read_signal_mutex(philo->signal, philo->signal_mutex))
	{
		leave_forks(philo);
		return (1);
	}
	if (should_philosopher_die(philo))
	{
		leave_forks(philo);
		philosopher_die(philo);
		return (0);
	}
	philo_message(philo->id, TAKE_FORK_COLOR "has taken a fork" COLOR_RESET "\n");
	return (1);
}

void	philosopher_eat(t_philosopher *philo)
{
	if (should_philosopher_die(philo))
		philosopher_die(philo);
	if (read_signal_mutex(philo->signal, philo->signal_mutex))
		return ;
	if (!take_forks(philo)
		|| read_signal_mutex(philo->signal, philo->signal_mutex))
	{
		leave_forks(philo);
		return ;
	}
	philo->last_meal_time = get_time();
	philo_message(philo->id, EAT_COLOR "is eating" COLOR_RESET "\n");
	msleep(philo->config->eat_time);
	leave_forks(philo);
	philo->eat_count += 1;
	if (philo->config->eat_count > 0
		&& philo->eat_count >= philo->config->eat_count)
	{
		pthread_mutex_lock(philo->signal_mutex);
		*(philo->signal) = 1;
		pthread_mutex_unlock(philo->signal_mutex);
	}
}

void	philosopher_sleep(t_philosopher *philo)
{
	long	diff;

	if (read_signal_mutex(philo->signal, philo->signal_mutex))
		return ;
	philo_message(philo->id, SLEEP_COLOR "is sleeping" COLOR_RESET "\n");
	diff = philo->config->starve_time - philo->config->sleep_time;
	if (diff <= 0)
	{
		msleep(philo->config->starve_time);
		//philosopher_die(data);
	}
	else
		msleep(philo->config->sleep_time);
}
