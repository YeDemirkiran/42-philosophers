/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval_sleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:10:37 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/16 01:29:22 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <unistd.h>

#include "structs/s_philosopher.h"
#include "modules/philosophers.h"
#include "modules/utils.h"
#include "macros/status.h"

#define SLEEP_INTERVAL 200

/**
 * @brief Sleeps for ms duration, but does it in intervals.
 * Checks whether the philosopher has died with each interval and exits
 * early.
 *
 * @return 0 on failure, 1 on success.
 */
int	interval_sleep(long ms, t_philosopher *philo)
{
	long	sleep_time;
	long	timer;

	if (philo == NULL || ms < 0)
		return (0);
	else if (ms == 0)
		return (1);
	timer = get_time();
	if (timer == -1)
	{
		philo_error("internal: Couldn't get time during interval_sleep");
		return (0);
	}
	sleep_time = timer + ms;
	while (timer < sleep_time)
	{
		if (!should_philo_continue(philo))
			break ;
		if (usleep(SLEEP_INTERVAL) != SUCCESS)
		{
			philo_error("internal: Couldn't sleep during interval_sleep");
			return (0);
		}
		timer = get_time();
		if (timer == -1)
		{
			philo_error("internal: Couldn't get time during interval_sleep");
			return (0);
		}
	}
	return (1);
}
