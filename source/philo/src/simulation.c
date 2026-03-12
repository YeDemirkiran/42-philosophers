/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:37:02 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/12 16:47:15 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <unistd.h>
#include <macros/status.h>

#include "structs/s_table.h"
#include "modules/philosophers.h"
#include "modules/utils.h"

#define DEATH_COLOR "\033[1;91m"
#define COLOR_RESET "\033[0m"

/**
 * @brief Checks if any philo has died
 * @return -1 if no philosopher has died, and
 * the ID of the dead philosopher otherwise.
 */
static int	any_philo_dead(t_philosopher *philos, size_t count)
{
	size_t	i;
	long	time;
	long	starve_time;
	long	last_meal_time;

	i = 0;
	starve_time = philos->config->starve_time;
	while (i < count)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		last_meal_time = philos[i].last_meal_time;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		time = get_time();
		if (time - last_meal_time >= starve_time)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Checks if all philos have eaten enough.
 *
 * @return 1 if all philos has eaten, 0 otherwise.
 */
static int	all_philos_eaten(t_philosopher *philos, size_t philo_count,
	size_t max_eat_count)
{
	size_t	i;
	size_t	eat_count;

	if (max_eat_count == 0)
		return (0);
	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		eat_count = philos[i].eat_count;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		if (eat_count < max_eat_count)
			return (0);
		i++;
	}
	return (1);
}

static void	monitor_philosophers(t_table *table,
	t_philosopher *philos, size_t philo_count)
{
	int	dead_id;
	int	max_eat;

	while (1)
	{
		usleep(100);
		dead_id = any_philo_dead(philos, philo_count);
		max_eat = all_philos_eaten(philos, philo_count,
				table->config.eat_count);
		if (dead_id >= 0 || max_eat)
		{
			pthread_mutex_lock(&table->over_mutex);
			table->dinner_over = 1;
			pthread_mutex_unlock(&table->over_mutex);
			if (dead_id >= 0)
				philo_message(dead_id,
					DEATH_COLOR "died" COLOR_RESET "\n", get_time());
			break ;
		}
	}
}

/**
 * @brief Starts the dinner simulation and the monitor.
 *
 * The monitor keeps checking every philosopher in an interval.
 * When a philosopher dies or all philosophers has eaten enough, the dinner
 * stops.
 */
void	start_simulation(t_table *table)
{
	int		res;
	size_t	philo_count;

	philo_count = table->config.philo_count;
	res = start_philosophers(table, philo_count);
	if (res != (int)philo_count)
	{
		pthread_mutex_lock(&table->over_mutex);
		table->dinner_over = 1;
		pthread_mutex_unlock(&table->over_mutex);
	}
	monitor_philosophers(table, table->philosophers, philo_count);
	join_philosophers(table->philosophers, philo_count);
}
