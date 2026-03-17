/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 06:38:59 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 10:06:40 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stddef.h>

#include "macros/status.h"

/**
 * @brief Returns the current time in milliseconds since the start
 * of the program.
 * @return -1 on error, time in milliseconds otherwise.
 * @note Call once in the main thread to initialize epoch. Otherwise,
 * race conditions may occur.
 */
long	get_time(void)
{
	static long				epoch = -1;
	long					current_time;
	long					timestamp;
	struct timeval			tv;

	if (gettimeofday(&tv, NULL) != SUCCESS)
		return (-1);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (epoch < 0)
		epoch = current_time;
	timestamp = current_time - epoch;
	return (timestamp);
}
