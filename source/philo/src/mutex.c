/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:20:11 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/06 14:58:56 by yademirk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

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

int	init_mutexes(pthread_mutex_t **mutexes, int count)
{
	int				res;
	int				i;

	*mutexes = malloc(sizeof(pthread_mutex_t) * count);
	if (!(*mutexes))
		return (false);
	i = 0;
	while (i < count)
	{
		res = pthread_mutex_init(*mutexes + i, NULL);
		if (res != true)
		{
			destroy_mutexes(*mutexes + count, i);
			return (false);
		}
		i++;
	}
	return (true);
}
