/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:37:02 by yademirk          #+#    #+#             */
/*   Updated: 2025/09/23 20:53:40 by yademirk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <macros/status.h>
#include <structs/s_table.h>
#include <modules/philosophers/philosophers.h>
#include <modules/philosophers/philosophers_utils.h>

void	start_simulation(t_table *table)
{
	int	res;

	res = start_philosophers(table, table->config.philo_count,
			philosopher_routine);
	if (res != (int)table->config.philo_count)
		table->dinner_over = 1;
	join_philosophers(table->philosophers, res);
}
