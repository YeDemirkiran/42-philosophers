/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:35:34 by yademirk          #+#    #+#             */
/*   Updated: 2025/10/15 01:21:36 by yademirk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <pthread.h>

#include <structs/s_thread_data.h>

#include <modules/philosophers/philosophers.h>
#include <modules/philosophers/philosophers_utils.h>

// colors
#define THINK_COLOR "\e[1;93m"
#define TAKE_FORK_COLOR "\e[1;37m"
#define EAT_COLOR "\e[1;92m"
#define SLEEP_COLOR "\e[1;96m"
#define DEATH_COLOR "\e[1;91m"
#define COLOR_RESET "\e[0m"

void	philosopher_die(t_thread_data *data, long time)
{
	pthread_mutex_lock(data->signal_mutex);
	if (*data->signal == 1)
	{
		pthread_mutex_unlock(data->signal_mutex);
		return ;
	}
	*(data->signal) = 1;
	pthread_mutex_unlock(data->signal_mutex);
	printf_philosopher(data->print_mutex, time, *data->philosopher->id,
		DEATH_COLOR "died" COLOR_RESET "\n");
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
	long	time;

	if (read_signal_mutex(data->signal, data->signal_mutex))
		return (1);
	time = time_philosopher(data, 0);
	if (should_philosopher_die(data, time))
	{
		philosopher_die(data, data->last_meal_time + data->config->starve_time);
		return (0);
	}
	printf_philosopher(data->print_mutex, time, *data->philosopher->id,
		THINK_COLOR "is thinking" COLOR_RESET "\n");
	if (*data->philosopher->id % 2 == 0)
		pthread_mutex_lock(data->philosopher->left_fork);
	else
		pthread_mutex_lock(data->philosopher->right_fork);
	if (read_signal_mutex(data->signal, data->signal_mutex))
	{
		//pthread_mutex_unlock(data->philosopher->left_fork);
		return (1);
	}
	time = time_philosopher(data, 0);
	if (should_philosopher_die(data, time))
	{
		philosopher_die(data, data->last_meal_time + data->config->starve_time);
		return (0);
	}
	printf_philosopher(data->print_mutex, time, *data->philosopher->id,
		TAKE_FORK_COLOR "has taken a fork" COLOR_RESET "\n");
	if (data->philosopher->left_fork == data->philosopher->right_fork)
	{
		time_philosopher(data, data->config->starve_time);
		philosopher_die(data, data->last_meal_time + data->config->starve_time);
		return (0);
	}
	if (*data->philosopher->id % 2 == 0)
		pthread_mutex_lock(data->philosopher->right_fork);
	else
		pthread_mutex_lock(data->philosopher->left_fork);
	if (read_signal_mutex(data->signal, data->signal_mutex))
	{
		//leave_forks(data);
		return (1);
	}
	time = time_philosopher(data, 0);
	if (should_philosopher_die(data, time))
	{
		philosopher_die(data, data->last_meal_time + data->config->starve_time);
		return (0);
	}
	printf_philosopher(data->print_mutex, time, *data->philosopher->id,
		TAKE_FORK_COLOR "has taken a fork" COLOR_RESET "\n");
	return (1);
}

void	philosopher_eat(t_thread_data *data)
{
	long	time;

	time = time_philosopher(data, 0);
	if (should_philosopher_die(data, time))
	{
		// printf("%i DEAAAD\n", *data->philosopher->id);
		// fflush(stdout);
		philosopher_die(data, data->last_meal_time + data->config->starve_time);
	}
	// else
	// {
	// 	printf("%i NOT DEAAAD\n", *data->philosopher->id);
	// 	fflush(stdout);
	// }
	if (read_signal_mutex(data->signal, data->signal_mutex))
		return ;
	if (!take_forks(data)
		|| read_signal_mutex(data->signal, data->signal_mutex))
	{
		leave_forks(data);
		return ;
	}
	time = time_philosopher(data, 0);
	data->last_meal_time = time;
	printf_philosopher(data->print_mutex, time, *data->philosopher->id,
		EAT_COLOR "is eating" COLOR_RESET "\n");
	time_philosopher(data, data->config->eat_time);
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
	long	time;
	long	diff;

	if (read_signal_mutex(data->signal, data->signal_mutex))
		return ;
	time = time_philosopher(data, 0);
	printf_philosopher(data->print_mutex, time, *data->philosopher->id,
		SLEEP_COLOR "is sleeping" COLOR_RESET "\n");
	diff = data->config->starve_time - data->config->sleep_time;
	if (diff <= 0)
	{
		time = time_philosopher(data, data->config->starve_time);
		// time = data->last_meal_time + data->config->starve_time;
		philosopher_die(data, time);
	}
	else
		time_philosopher(data, data->config->sleep_time);
}
