/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval_sleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:10:37 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/12 15:56:11 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <unistd.h>

#include "structs/s_philosopher.h"
#include "modules/philosophers.h"
#include "modules/utils.h"

#define SLEEP_INTERVAL 1000

/**
 * @brief Sleeps for ms duration, but does it in intervals.
 * Checks whether the philosopher has died with each interval and exits
 * early.
 */
void	interval_sleep(long ms, t_philosopher *philo)
{
	long	sleep_time;
	long	timer;

	timer = get_time();
	sleep_time = timer + ms;
	while (timer < sleep_time)
	{
		if (!should_philo_continue(philo))
			break ;
		usleep(SLEEP_INTERVAL);
		timer = get_time();
	}
}
