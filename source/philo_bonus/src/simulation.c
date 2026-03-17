/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:37:02 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 13:21:18 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "structs/s_table.h"
#include "modules/philosophers.h"
#include "modules/utils.h"
#include "philo_messages.h"
#include "macros/status.h"

/**
 * @brief Sends the SIGTERM signal to all philosophers (child processes).
 */
static void	kill_philosophers(t_philosopher *philos, size_t philo_count)
{
	size_t	i;

	i = 0;
	while (i < philo_count)
	{
		kill(philos[i].pid, SIGTERM);
		i++;
	}
}

/**
 * @brief Waits for the simulation to end.
 * 
 * First, it waits for a process to end. After it ends, it checks the
 * exit status for philosopher state: Did we exit because of an error,
 * or we died, or did we eat enough?
 * 
 * If we ate enough, the loop keeps working. Otherwise, all philosophers
 * are killed, and an optional death message is printed.
 */
static void	wait_philosophers(t_philosopher *philos, size_t philo_count)
{
	int		exit_code;
	pid_t	current;
	size_t	i;

	exit_code = 0;
	while (1)
	{
		current = waitpid(-1, &exit_code, 0);
		if (current == -1)
			break ;
		if (WEXITSTATUS(exit_code) != 0)
		{
			i = 0;
			while (i < philo_count && philos[i].pid != current)
				i++;
			if (WEXITSTATUS(exit_code) == 2)
				philo_message(philos + i, DEATH_MESSAGE, get_time());
			kill_philosophers(philos, philo_count);
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
	if (result == 0 || result != philo_count || result != philo_count)
	{
		philo_error("internal: Couldn't start all philosophers, aborting");
		kill_philosophers(table->philosophers, philo_count);
		return ;
	}
	wait_philosophers(table->philosophers, philo_count);
}
