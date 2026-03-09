/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:35:34 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/09 15:14:32 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "structs/s_philosopher.h"
#include "modules/utils.h"
#include "modules/philosophers/philosophers.h"
#include "modules/philosophers/philosophers_utils.h"

// colors

#define THINK_COLOR "\033[1;93m"
#define TAKE_FORK_COLOR "\033[1;37m"
#define EAT_COLOR "\033[1;92m"
#define SLEEP_COLOR "\033[1;96m"
#define COLOR_RESET "\033[0m"

// messages

#define EAT_MESSAGE EAT_COLOR "is eating" COLOR_RESET "\n"
#define THINK_MESSAGE THINK_COLOR "is thinking" COLOR_RESET "\n"
#define FORK_MESSAGE TAKE_FORK_COLOR "has taken a fork" COLOR_RESET "\n"
#define SLEEP_MESSAGE SLEEP_COLOR "is sleeping" COLOR_RESET "\n"

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
	philo_message(philo->id, THINK_MESSAGE, -1);
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
	philo_message(philo->id, FORK_MESSAGE, -1);
	if (philo->left_fork == philo->right_fork || philo->right_fork == NULL)
	{
		interval_sleep(philo->config->starve_time, philo);
		pthread_mutex_unlock(first_fork);
		//should_philo_continue(philo);
		return (0);
	}
	if (first_fork == philo->left_fork && philo->right_fork != NULL)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (!should_philo_continue(philo))
	{
		leave_forks(philo);
		return (0);
	}
	philo_message(philo->id, FORK_MESSAGE, -1);
	return (1);
}

int	philosopher_eat(t_philosopher *philo)
{
	if (!take_forks(philo))
		return (0);
	philo->last_meal_time = get_time();
	if (!should_philo_continue(philo))
	{
		leave_forks(philo);
		return (0);
	}
	philo_message(philo->id, EAT_MESSAGE, philo->last_meal_time);
	interval_sleep(philo->config->eat_time, philo);
	leave_forks(philo);
	philo->eat_count += 1;
	// TODO: Refine eat count logic
	// if (philo->config->eat_count > 0
	// 	&& philo->eat_count >= philo->config->eat_count)
	// {
	// 	pthread_mutex_lock(philo->signal_mutex);
	// 	*(philo->signal) = 1;
	// 	pthread_mutex_unlock(philo->signal_mutex);
	// }
	return (1);
}

void	philosopher_sleep(t_philosopher *philo)
{
	if (!should_philo_continue(philo))
		return ;
	philo_message(philo->id, SLEEP_MESSAGE, -1);
	interval_sleep(philo->config->sleep_time, philo);
}
