/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:35:53 by yademirk          #+#    #+#             */
/*   Updated: 2025/09/09 12:39:26 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include <structs/s_table.h>
#include <modules/table.h>
#include <modules/simulation.h>
#include <macros/status.h>

static void	wrong_usage(void)
{
	printf("usage: philo philo_count time_to_die time_to_eat time_to_sleep"
		" [max_eat_count]\n");
}

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc < 5 || argc > 6)
	{
		wrong_usage();
		return (EXIT_FAILURE);
	}
	if (init_table(&table, argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	start_simulation(&table);
	clear_table(&table);
	return (EXIT_SUCCESS);
}
