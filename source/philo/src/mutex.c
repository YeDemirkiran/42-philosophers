/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:20:11 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/15 21:51:29 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>

#include <macros/status.h>

/**
 * @brief Destroys all mutexes and frees the array.
 */
void	destroy_mutexes(pthread_mutex_t *mutexes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(mutexes + i);
		i++;
	}
	free(mutexes);
}

/**
 * @brief Malloc's the given mutex array by the given count and
 * initalizes all of them.
 *
 * @return 0 on success, 1 on failure.
 */
int	init_mutexes(pthread_mutex_t **mutexes, int count)
{
	int				res;
	int				i;

	*mutexes = malloc(sizeof(pthread_mutex_t) * count);
	if (*mutexes == NULL)
		return (FAILURE);
	i = 0;
	while (i < count)
	{
		res = pthread_mutex_init(*mutexes + i, NULL);
		if (res != SUCCESS)
		{
			destroy_mutexes(*mutexes, i);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
