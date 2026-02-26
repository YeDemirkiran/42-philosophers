/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:31:44 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/25 09:15:37 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include <macros/status.h>
#include <structs/s_philosopher.h>
#include <structs/s_table.h>

#include "modules/utils.h"

t_byte	should_philosopher_die(t_philosopher *philo)
{
	long	current_time;

	current_time = get_time();
	return (current_time
		>= philo->last_meal_time + (long)(philo->config->starve_time));
}

void	init_philosophers(t_philosopher *philos, t_table *table,
	int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		philos[i].id = i;
		philos[i].eat_count = 0;
		philos[i].last_meal_time = 0;
		philos[i].left_fork = table->forks + i;
		if (philo_count < 2)
			philos[i].right_fork = NULL;
		else
			philos[i].right_fork = table->forks + ((i + 1) % philo_count);
		philos[i].config = &(table->config);
		philos[i].signal = &(table->dinner_over);
		philos[i].signal_mutex = &(table->over_mutex);
		i++;
	}
}

void	join_philosophers(t_philosopher *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
}
