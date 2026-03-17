/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:16:51 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 10:05:17 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <structs/s_table.h>

/**
 * @return 0 if the philosopher should stop, 1 if it should continue.
 */
t_byte	should_philo_continue(t_philosopher *philo);

/**
 * @brief Initializes the philosophers of a table,
 * then starts each of them in their own thread.
 *
 * @return 0 on error, otherwise returns the number of
 * successfully started threads.
 */
size_t	start_philosophers(t_table *table, size_t count);

#endif
