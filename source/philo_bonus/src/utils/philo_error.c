/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 22:01:00 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/14 22:03:48 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/**
 * @brief Prints an error message to the standard error
 * in the "philo: error: [message]" format.
 *
 * @note Prints "philo: error: Unknown error" if msg is NULL.
 */
void	philo_error(const char *msg)
{
	size_t	len;

	write(STDERR_FILENO, "philo: error: ", 14);
	if (msg == NULL)
	{
		write(STDERR_FILENO, "Unknown error\n", 14);
		return ;
	}
	len = 0;
	while (msg[len] != '\0')
		len++;
	write(STDERR_FILENO, msg, len);
	write(STDERR_FILENO, "\n", 1);
}
