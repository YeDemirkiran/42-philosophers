/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:22:55 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 09:59:28 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "structs/s_table.h"
#include "macros/status.h"
#include "modules/utils.h"
#include "modules/philosophers.h"

#define ARG_1_ERR "Argument philo_number must be a positive integer"
#define ARG_2_ERR "Argument time_to_die must be zero or a positive integer"
#define ARG_3_ERR "Argument time_to_eat must be zero or a positive integer"
#define ARG_4_ERR "Argument time_to_sleep must be zero or a positive integer"
#define ARG_5_ERR "Optional argument max_eat_count must be a positive integer"

#define FORK_SEMAPHORE_NAME "/philo_forks"
#define PRINT_SEMAPHORE_NAME "/philo_print"

static t_byte	init_config_numbers(long long config_numbers[5], char **argv)
{
	const char	*err_msg[4] = {ARG_1_ERR, ARG_2_ERR, ARG_3_ERR, ARG_4_ERR};
	size_t		i;

	config_numbers[0] = ft_atol(argv[0]);
	if (config_numbers[0] <= 0)
	{
		philo_error(err_msg[0]);
		return (FAILURE);
	}
	i = 1;
	while (i < 4)
	{
		config_numbers[i] = ft_atol(argv[i]);
		if (config_numbers[i] < 0)
		{
			philo_error(err_msg[i]);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Validates the first 4 config numbers and whether they are positive
 * integers.
 *
 * @return 0 on success, 1 on failure.
 */
static t_byte	validate_config(long long config_numbers[5])
{
	if (config_numbers == NULL)
		return (FAILURE);
	if (config_numbers[0] < 0 || config_numbers[1] < 0
		|| config_numbers[2] < 0 || config_numbers[3] < 0)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * @brief Initializes the table's config and rules.
 *
 * @return 0 on success, 1 on failure.
 *
 * @note The optional 5th argument "max_eat_count" is set to 0
 * if it's not set by the user.
 */
static t_byte	init_config(t_config *config, int argc, char **argv)
{
	long long	config_numbers[5];

	if (config == NULL || argc <= 0 || argv == NULL)
		return (FAILURE);
	if (init_config_numbers(config_numbers, argv + 1) != SUCCESS)
		return (FAILURE);
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
			philo_error(ARG_5_ERR);
			return (FAILURE);
		}
	}
	config->eat_count = config_numbers[4];
	return (SUCCESS);
}

/**
 * @brief Inits the dinner table.
 *
 * @return 0 on success, 1 on failure.
 */
t_byte	init_table(t_table *table, int argc, char **argv)
{
	table->dinner_over = 0;
	if (init_config(&(table->config), argc, argv) != SUCCESS)
		return (FAILURE);
	table->philosophers = malloc(sizeof(t_philosopher)
		* table->config.philo_count);
	if (table->philosophers == NULL)
	{
		philo_error("internal: Can't allocate memory for philosophers");
		return (FAILURE);
	}
	table->forks = sem_open(FORK_SEMAPHORE_NAME, O_CREAT,
		0644, table->config.philo_count);
	if (table->forks == SEM_FAILED)
	{
		philo_error("internal: Can't initialize the fork semaphore");
		return (FAILURE);
	}
	sem_unlink(FORK_SEMAPHORE_NAME);
	table->print_semaphore = sem_open(PRINT_SEMAPHORE_NAME, O_CREAT,
		0644, 0);
	if (table->print_semaphore == SEM_FAILED)
	{
		sem_close(table->forks);
		philo_error("internal: Can't initialize the print semaphore");
		return (FAILURE);
	}
	sem_unlink(PRINT_SEMAPHORE_NAME);
	return (SUCCESS);
}

/**
 * @brief Clears the dinner table.
 *
 * - Clears and frees all philosophers
 *
 * - Destroys all semaphores
 */
void	clear_table(t_table *table)
{
	if (table == NULL)
		return ;
	clear_philosophers(table->philosophers, table->config.philo_count);
}
