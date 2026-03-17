/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:37:02 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 09:33:26 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <unistd.h>
#include <sys/wait.h>

#include "structs/s_table.h"
#include "modules/philosophers.h"
#include "modules/utils.h"
#include "philo_messages.h"
#include "macros/status.h"

#ifndef MONITOR_INTERVAL_MS
# define MONITOR_INTERVAL_MS 1000
#endif

#define MONITOR_MSG_1 "internal: The monitor thread can't sleep, aborting"
#define MONITOR_MSG_2 "internal: Can't check the death of philosophers"
#define MONITOR_MSG_3 "internal: Can't check the eat count of philosophers"

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

static void	wait_philosophers(t_philosopher *philos, size_t philo_count)
{
	int	*exit_code;

	while (1)
	{
		if (waitpid(-1, exit_code, 0) == -1)
			break ;
		if (WEXITSTATUS(*exit_code) != 0)
		{
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
