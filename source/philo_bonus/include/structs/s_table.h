/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_table.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:53:44 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/17 10:53:17 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_TABLE_H
# define S_TABLE_H

# include <semaphore.h>

# include <structs/s_philosopher.h>
# include <structs/s_config.h>

typedef struct s_table
{
	t_config		config;
	t_philosopher	*philosophers;
	sem_t			*forks;
	sem_t			*print_semaphore;
	sem_t			*eating_semaphore;
}	t_table;

#endif
