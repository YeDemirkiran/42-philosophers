/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:22:55 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/14 13:03:25 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "structs/s_table.h"
#include "macros/status.h"
#include "modules/mutex.h"
#include "modules/utils.h"

static int	validate_config(long long config_numbers[5])
{
	if (config_numbers[0] < 0 || config_numbers[1] < 0
		|| config_numbers[2] < 0 || config_numbers[3] < 0)
		return (FAILURE);
	return (SUCCESS);
}

static int	init_config(t_config *config, int argc, char **argv)
{
	long long	config_numbers[5];

	if (!argv[1] || !argv[2] || !argv[3] || !argv[4])
		return (FAILURE);
	config_numbers[0] = ft_atol(argv[1]);
	if (config_numbers[0] <= 0)
	{
		write(STDERR_FILENO, "philo: error: argument philo_number must be a positive integer\n", 64);
		return (FAILURE);
	}
	config_numbers[1] = ft_atol(argv[2]);
	if (config_numbers[1] <= 0)
	{
		write(STDERR_FILENO, "philo: error: argument time_to_die must be a positive integer\n", 63);
		return (FAILURE);
	}
	config_numbers[2] = ft_atol(argv[3]);
	if (config_numbers[2] <= 0)
	{
		write(STDERR_FILENO, "philo: error: argument time_to_eat must be a positive integer\n", 63);
		return (FAILURE);
	}
	config_numbers[3] = ft_atol(argv[4]);
	if (config_numbers[3] <= 0)
	{
		write(STDERR_FILENO, "philo: error: argument time_to_sleep must be a positive integer\n", 65);
		return (FAILURE);
	}
	if (validate_config(config_numbers) == FAILURE)
		return (FAILURE);
	config->philo_count = config_numbers[0];
	config->starve_time = config_numbers[1];
	config->eat_time = config_numbers[2];
	config->sleep_time = config_numbers[3];
	config_numbers[4] = 0;
	if (argc > 5 && argv[5])
	{
		config_numbers[4] = ft_atol(argv[5]);
		if (config_numbers[4] <= 0)
		{
			write(STDERR_FILENO, "philo: error: optional argument max_eat_count must be a positive integer\n", 74);
			return (FAILURE);
		}
	}
	config->eat_count = config_numbers[4];
	return (SUCCESS);
}

int	init_table(t_table *table, int argc, char **argv)
{
	table->dinner_over = 0;
	if (init_config(&(table->config), argc, argv) != SUCCESS)
		return (FAILURE);
	if (pthread_mutex_init(&(table->over_mutex), NULL) != SUCCESS)
		return (FAILURE);
	table->philosophers = malloc(sizeof(t_philosopher)
			* table->config.philo_count);
	if (!table->philosophers)
	{
		pthread_mutex_destroy(&(table->over_mutex));
		return (FAILURE);
	}
	if (init_mutexes(&(table->forks), table->config.philo_count) != SUCCESS)
	{
		pthread_mutex_destroy(&(table->over_mutex));
		free(table->philosophers);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	clear_philosophers(t_philosopher *philosophers, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philosophers[i].meal_mutex);
		i++;
	}
	free(philosophers);
}

void	clear_table(t_table *table)
{
	clear_philosophers(table->philosophers, table->config.philo_count);
	destroy_mutexes(table->forks, table->config.philo_count);
	pthread_mutex_destroy(&(table->over_mutex));
}
