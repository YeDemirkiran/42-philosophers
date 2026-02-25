/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:46:31 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/25 08:41:53 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_UTILS_H
# define PHILOSOPHERS_UTILS_H

# include <pthread.h>
# include <structs/s_philosopher.h>

t_byte	should_philosopher_die(t_philosopher *philo);
void	init_philosophers(t_philosopher *philos, t_table *table,
		int philo_count);
void	join_philosophers(t_philosopher *philos, int count);
void	printf_philosopher(pthread_mutex_t *mutex,
			long timestamp, int philo_id, char *string);

#endif
