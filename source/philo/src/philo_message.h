/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_message.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 21:28:44 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/20 21:31:35 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_MESSAGE_H
# define PHILO_MESSAGE_H

/**
 * @brief Takes a message and prints it in the "philo_id timestamp message"
 * format. Acquires the print lock before doing it, and automatically unlocks
 * the mutex after printing.
 *
 * @return Error if mutex_lock or mutex_unlock fails, and whatever printf
 * returns otherwise.
 */
int	*philo_message(int philo_id, long timestamp, const char *message);

#endif
