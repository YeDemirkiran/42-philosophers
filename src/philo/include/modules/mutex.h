/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:21:29 by yademirk          #+#    #+#             */
/*   Updated: 2025/09/04 23:47:49 by yademirk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MUTEX_H
# define MUTEX_H

# include <pthread.h>

int				init_mutexes(pthread_mutex_t **mutexes, int count);
void			destroy_mutexes(pthread_mutex_t *mutexes, int count);

#endif
