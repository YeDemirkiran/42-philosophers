/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 11:14:25 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/31 11:14:46 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <fcntl.h>

/**
 * @brief Creates a named semaphore with count and immediately
 * unlinks it.
 */
sem_t	*create_sem(const char *name, int count)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT, 0644, count);
	if (sem == SEM_FAILED)
		return (SEM_FAILED);
	sem_unlink(name);
	return (sem);
}