/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:35:34 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/25 07:12:48 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

#include "structs/s_thread_data.h"
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

void	philosopher_die(t_thread_data *data)
{
	pthread_mutex_lock(data->signal_mutex);
	if (*data->signal == 1)
	{
		pthread_mutex_unlock(data->signal_mutex);
		return ;
	}
	*(data->signal) = 1;
	pthread_mutex_unlock(data->signal_mutex);
	philo_message(data->philosopher->id, DEATH_COLOR "died" COLOR_RESET "\n");
}

static void	leave_forks(t_thread_data *data)
{
	pthread_mutex_unlock(data->philosopher->left_fork);
	if (data->philosopher->left_fork == data->philosopher->right_fork)
		return ;
	pthread_mutex_unlock(data->philosopher->right_fork);
}

static int	take_forks(t_thread_data *data)
{
	pthread_mutex_t	*first_fork;

	if (read_signal_mutex(data->signal, data->signal_mutex))
		return (1);
	if (should_philosopher_die(data))
	{
		philosopher_die(data);
		return (0);
	}
	philo_message(data->philosopher->id, THINK_COLOR "is thinking" COLOR_RESET "\n");
	if (data->philosopher->left_fork < data->philosopher->right_fork)
		first_fork = data->philosopher->left_fork;
	else
		first_fork = data->philosopher->right_fork;
	pthread_mutex_lock(first_fork);
	if (read_signal_mutex(data->signal, data->signal_mutex))
	{
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	if (should_philosopher_die(data))
	{
		philosopher_die(data);
		return (0);
	}
	philo_message(data->philosopher->id, TAKE_FORK_COLOR "has taken a fork" COLOR_RESET "\n");
	if (data->philosopher->left_fork == data->philosopher->right_fork)
	{
		msleep(data->config->starve_time);
		pthread_mutex_unlock(first_fork);
		philosopher_die(data);
		return (0);
	}
	if (first_fork == data->philosopher->left_fork)
		pthread_mutex_lock(data->philosopher->right_fork);
	else
		pthread_mutex_lock(data->philosopher->left_fork);
	if (read_signal_mutex(data->signal, data->signal_mutex))
	{
		leave_forks(data);
		return (1);
	}
	if (should_philosopher_die(data))
	{
		leave_forks(data);
		philosopher_die(data);
		return (0);
	}
	philo_message(data->philosopher->id, TAKE_FORK_COLOR "has taken a fork" COLOR_RESET "\n");
	return (1);
}

void	philosopher_eat(t_thread_data *data)
{
	if (should_philosopher_die(data))
		philosopher_die(data);
	if (read_signal_mutex(data->signal, data->signal_mutex))
		return ;
	if (!take_forks(data)
		|| read_signal_mutex(data->signal, data->signal_mutex))
	{
		leave_forks(data);
		return ;
	}
	data->last_meal_time = get_time();
	philo_message(data->philosopher->id, EAT_COLOR "is eating" COLOR_RESET "\n");
	msleep(data->config->eat_time);
	leave_forks(data);
	data->philosopher->eat_count += 1;
	if (data->config->eat_count > 0
		&& data->philosopher->eat_count >= data->config->eat_count)
	{
		pthread_mutex_lock(data->signal_mutex);
		*(data->signal) = 1;
		pthread_mutex_unlock(data->signal_mutex);
	}
}

void	philosopher_sleep(t_thread_data *data)
{
	long	diff;

	if (read_signal_mutex(data->signal, data->signal_mutex))
		return ;
	philo_message(data->philosopher->id, SLEEP_COLOR "is sleeping" COLOR_RESET "\n");
	diff = data->config->starve_time - data->config->sleep_time;
	if (diff <= 0)
	{
		msleep(data->config->starve_time);
		philosopher_die(data);
	}
	else
		msleep(data->config->sleep_time);
}
