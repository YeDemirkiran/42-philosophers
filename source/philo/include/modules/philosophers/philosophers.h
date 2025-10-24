/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:16:51 by yademirk          #+#    #+#             */
/*   Updated: 2025/10/03 22:11:12 by yademirk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <structs/s_thread_data.h>
# include <structs/s_table.h>

long	time_philosopher(t_thread_data *data, long ms);
t_byte	read_signal_mutex(t_byte *signal, pthread_mutex_t *mutex);
void	*philosopher_routine(void *data);
int		start_philosophers(t_table *table, int count,
			void *(*philo_routine)(void *));

#endif
