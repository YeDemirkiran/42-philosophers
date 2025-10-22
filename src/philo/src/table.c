/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:22:55 by yademirk          #+#    #+#             */
/*   Updated: 2025/10/06 20:41:34 by yademirk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stdlib.h>

#include <structs/s_table.h>
#include <macros/status.h>
#include <modules/mutex.h>
#include <modules/utils/convert.h>
#include <modules/philosophers/philosophers.h>
#include <modules/philosophers/philosophers_utils.h>

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
	config_numbers[1] = ft_atol(argv[2]);
	config_numbers[2] = ft_atol(argv[3]);
	config_numbers[3] = ft_atol(argv[4]);
	if (validate_config(config_numbers) == FAILURE)
		return (FAILURE);
	config->philo_count = config_numbers[0];
	config->starve_time = config_numbers[1];
	config->eat_time = config_numbers[2];
	config->sleep_time = config_numbers[3];
	if (argc > 5 && argv[5])
		config_numbers[4] = ft_atol(argv[5]);
	else
		config_numbers[4] = -1;
	config->eat_count = config_numbers[4] * (config_numbers[4] >= 0);
	return (SUCCESS);
}

int	init_table(t_table *table, int argc, char **argv)
{
	table->dinner_over = 1;
	if (pthread_mutex_init(&(table->over_mutex), NULL) != SUCCESS)
		return (FAILURE);
	if (pthread_mutex_init(&(table->print_mutex), NULL) != SUCCESS)
		return (FAILURE);
	if (init_config(&(table->config), argc, argv) != SUCCESS)
		return (FAILURE);
	if (init_mutexes(&(table->forks), table->config.philo_count) != SUCCESS)
	{
		pthread_mutex_destroy(&(table->over_mutex));
		return (FAILURE);
	}
	table->philosophers = malloc(sizeof(t_philosopher)
			* table->config.philo_count);
	if (!table->philosophers)
	{
		destroy_mutexes(table->forks, table->config.philo_count);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	clear_table(t_table *table)
{
	free_philosophers(table->philosophers, table->config.philo_count);
	destroy_mutexes(table->forks, table->config.philo_count);
	pthread_mutex_destroy(&(table->over_mutex));
	pthread_mutex_destroy(&(table->print_mutex));
}
