/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:20:11 by yademirk          #+#    #+#             */
/*   Updated: 2025/09/09 12:39:40 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>

#include <macros/status.h>

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
		return (FAILURE);
	i = 0;
	while (i < count)
	{
		res = pthread_mutex_init(*mutexes + i, NULL);
		if (res != SUCCESS)
		{
			destroy_mutexes(*mutexes + count, i);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
