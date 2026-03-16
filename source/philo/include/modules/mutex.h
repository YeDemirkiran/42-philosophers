/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:21:29 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/16 07:38:56 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_H
# define MUTEX_H

# include <pthread.h>

# include "types/t_byte.h"

/**
 * @brief Malloc's the given mutex array by the given count and
 * initalizes all of them.
 *
 * @return 0 on success, 1 on failure.
 */
t_byte	init_mutexes(pthread_mutex_t **mutexes, int count);

/**
 * @brief Destroys all mutexes and frees the array.
 */
void	destroy_mutexes(pthread_mutex_t *mutexes, int count);

#endif
