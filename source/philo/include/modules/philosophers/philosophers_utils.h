/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:46:31 by yademirk          #+#    #+#             */
/*   Updated: 2025/10/12 20:40:39 by yademirk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PHILOSOPHERS_UTILS_H
# define PHILOSOPHERS_UTILS_H

# include <pthread.h>
# include <structs/s_philosopher.h>
# include <structs/s_thread_data.h>

t_byte	should_philosopher_die(t_thread_data *data, long current_time);
void	init_philosophers(t_philosopher *philos, pthread_mutex_t *forks,
			int philo_count);
void	join_philosophers(t_philosopher *philos, int count);
void	free_philosophers(t_philosopher *philos, int count);
void	printf_philosopher(pthread_mutex_t *mutex,
			long timestamp, int philo_id, char *string);

#endif
