/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:10:37 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/26 15:10:50 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <unistd.h>

/**
 * @brief Sleeps for the given milliseconds.
 */
long	msleep(long ms)
{
	return (usleep(ms * 1000));
}
