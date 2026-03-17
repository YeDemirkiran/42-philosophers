/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 21:25:01 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 10:00:56 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <semaphore.h>

#include "modules/utils.h"
#include "structs/s_philosopher.h"
#include "macros/status.h"

/**
 * @brief Takes a message and prints it in the "philo_id timestamp message"
 * format. Acquires the print semaphore before doing it, and
 * automatically posts it after printing.
 *
 * @return -1 on error (semaphore fails), and whatever printf
 * returns otherwise.
 */
int	philo_message(t_philosopher *philo, const char *message, long timestamp)
{
	int	result;

	if (sem_wait(philo->print_semaphore) != SUCCESS)
	{
		philo_error("internal: Can't wait philosopher message semaphore");
		return (-1);
	}
	result = printf("%li %i %s", timestamp, philo->id + 1, message);
	if (sem_post(philo->print_semaphore) != SUCCESS)
	{
		philo_error("internal: Can't post philosopher message semaphore");
		return (-1);
	}
	return (result);
}
