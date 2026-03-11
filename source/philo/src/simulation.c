/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:37:02 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/11 17:55:45 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <unistd.h>
#include <macros/status.h>
#include <structs/s_table.h>
#include <modules/philosophers/philosophers.h>
#include <modules/philosophers/philosophers_utils.h>
#include <modules/utils.h>

#define DEATH_COLOR "\033[1;91m"
#define COLOR_RESET "\033[0m"

void	detach_philosophers(t_philosopher *philos, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		pthread_detach(philos[i].thread_id);
		i++;
	}
}

int	any_philo_dead(t_philosopher *philos, size_t count)
{
	size_t	i;
	long	time;
	long	starve_time;

	i = 0;
	time = get_time();
	starve_time = philos->config->starve_time;
	while (i < count)
	{
		if (time - philos[i].last_meal_time >= starve_time)
			return (i);
		i++;
	}
	return (-1);
}

void	start_simulation(t_table *table)
{
	int		res;
	int		dead_id;
	size_t	philo_count;

	philo_count = table->config.philo_count;
	res = start_philosophers(table, philo_count, philosopher_routine);
	if (res != (int)philo_count)
		table->dinner_over = 1;
	detach_philosophers(table->philosophers, philo_count);
	while (1)
	{
		usleep(100);
		dead_id = any_philo_dead(table->philosophers, philo_count);
		if (dead_id >= 0)
		{
			pthread_mutex_lock(&table->over_mutex);
			table->dinner_over = 1;
			pthread_mutex_unlock(&table->over_mutex);
			philo_message(dead_id, DEATH_COLOR "died" COLOR_RESET "\n", -1);
			break ;
		}
	}
	usleep(20000);
}
