/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_philosopher.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:56:29 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/31 10:32:03 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_PHILOSOPHER_H
# define S_PHILOSOPHER_H

# include <semaphore.h>

# include "types/t_byte.h"
# include "structs/s_config.h"

typedef struct s_philosopher
{
	int			id;
	pid_t		pid;
	size_t		eat_count;
	long		last_meal_time;

	t_config	*config;
	sem_t		*forks;
	sem_t		*print_semaphore;
	sem_t		*eating_semaphore;
	sem_t		*death_semaphore;
	sem_t		*meal_semaphore;
}	t_philosopher;

#endif
