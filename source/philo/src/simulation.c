/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:37:02 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/15 22:40:36 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <unistd.h>
#include <macros/status.h>

#include "structs/s_table.h"
#include "modules/philosophers.h"
#include "modules/utils.h"

// for reference

#define DEATH_COLOR "\033[1;91m"
#define COLOR_RESET "\033[0m"

#define DEATH_MESSAGE "\033[1;91m" "died" "\033[0m" "\n"

#ifndef MONITOR_INTERVAL_MS
# define MONITOR_INTERVAL_MS 1000
#endif

/**
 * @brief Checks if any philo has died
 * @return -1 if no philosopher has died, -2 on errors, and
 * the ID of the dead philosopher otherwise.
 */
static int	any_philo_dead(t_philosopher *philos, size_t count)
{
	size_t	i;
	long	time;
	long	starve_time;
	long	last_meal_time;

	if (philos == NULL || philos->config == NULL || count == 0)
		return (-2);
	i = 0;
	starve_time = philos->config->starve_time;
	while (i < count)
	{
		if (pthread_mutex_lock(&philos[i].meal_mutex) != SUCCESS)
			return (-2);
		last_meal_time = philos[i].last_meal_time;
		if (pthread_mutex_unlock(&philos[i].meal_mutex) != SUCCESS)
			return (-2);
		time = get_time();
		if (time == -1)
			return (-2);
		if (time - last_meal_time >= starve_time)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Checks if all philos have eaten enough.
 *
 * @return -1 on error, 1 if all philos has eaten, 0 otherwise.
 */
static int	all_philos_eaten(t_philosopher *philos, size_t philo_count,
	size_t max_eat_count)
{
	size_t	i;
	size_t	eat_count;

	if (philos == NULL || philo_count == 0)
		return (-1);
	if (max_eat_count == 0)
		return (0);
	i = 0;
	while (i < philo_count)
	{
		if (pthread_mutex_lock(&philos[i].meal_mutex) != SUCCESS)
			return (-1);
		eat_count = philos[i].eat_count;
		if (pthread_mutex_unlock(&philos[i].meal_mutex) != SUCCESS)
			return (-1);
		if (eat_count < max_eat_count)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Runs in a loop and checks all philosophers' states in each
 * interval.
 *
 * In each philosopher, two properties are checked:
 *
 * - If it's dead (enough time has passed since the last meal time)
 *
 * - If it's eaten equal to  or more than the optional max_eat_count argument.
 *
 * Sleeps for MONITOR_INTERVAL_MS duration before each interval.
 */
static void	monitor_philosophers(t_table *table,
	t_philosopher *philos, size_t philo_count)
{
	int	dead_id;
	int	max_eat;

	while (1)
	{
		if (usleep(MONITOR_INTERVAL_MS) != SUCCESS)
		{
			pthread_mutex_lock(&table->over_mutex);
			table->dinner_over = 1;
			pthread_mutex_unlock(&table->over_mutex);
			philo_error("internal: The monitor thread can't sleep, aborting");
			return ;
		}
		dead_id = any_philo_dead(philos, philo_count);
		if (dead_id == -2)
		{
			pthread_mutex_lock(&table->over_mutex);
			table->dinner_over = 1;
			pthread_mutex_unlock(&table->over_mutex);
			philo_error("internal: Can't check the death of philosophers");
			return ;
		}
		max_eat = all_philos_eaten(philos, philo_count,
				table->config.eat_count);
		if (max_eat == -1)
		{
			pthread_mutex_lock(&table->over_mutex);
			table->dinner_over = 1;
			pthread_mutex_unlock(&table->over_mutex);
			philo_error("internal: Can't check the eat count of philosophers");
			return ;
		}
		if (dead_id >= 0 || max_eat)
		{
			pthread_mutex_lock(&table->over_mutex);
			table->dinner_over = 1;
			pthread_mutex_unlock(&table->over_mutex);
			if (dead_id >= 0)
				philo_message(dead_id, DEATH_MESSAGE, get_time());
			break ;
		}
	}
}

/**
 * @brief Starts the dinner simulation and the monitor.
 *
 * The monitor keeps checking every philosopher in an interval.
 * When a philosopher dies or all philosophers has eaten enough, the
 * simulation stops.
 */
void	start_simulation(t_table *table)
{
	size_t	result;
	size_t	philo_count;

	if (table == NULL)
		return ;
	philo_count = table->config.philo_count;
	if (philo_count == 0)
		return ;
	result = start_philosophers(table, philo_count);
	if (result == 0 || result != philo_count)
	{
		pthread_mutex_lock(&table->over_mutex);
		table->dinner_over = 1;
		pthread_mutex_unlock(&table->over_mutex);
		philo_error("internal: Couldn't start all philosophers, aborting");
	}
	else
		monitor_philosophers(table, table->philosophers, philo_count);
	join_philosophers(table->philosophers, philo_count);
}
