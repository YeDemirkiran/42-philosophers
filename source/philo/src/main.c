/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:35:53 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/14 22:05:29 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "structs/s_table.h"
#include "modules/table.h"
#include "modules/utils.h"
#include "modules/simulation.h"
#include "macros/status.h"

/**
 * @brief Prints the correct usage message.
 */
static void	on_wrong_usage_message(void)
{
	printf("usage: philo philo_count time_to_die time_to_eat time_to_sleep"
		" [max_eat_count]\n");
}

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc < 5 || argc > 6)
	{
		on_wrong_usage_message();
		return (EXIT_FAILURE);
	}
	if (init_table(&table, argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	if (get_time() == -1)
	{
		philo_error("Timing errors has occured");
		return (EXIT_FAILURE);
	}
	start_simulation(&table);
	clear_table(&table);
	return (EXIT_SUCCESS);
}
