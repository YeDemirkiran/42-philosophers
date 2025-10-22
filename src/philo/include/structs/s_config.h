/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_config.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:02:25 by yademirk          #+#    #+#             */
/*   Updated: 2025/09/23 20:59:27 by yademirk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef S_CONFIG_H
# define S_CONFIG_H

# include <stddef.h>

typedef struct s_config
{
	size_t			philo_count;
	unsigned long	starve_time;
	unsigned long	eat_time;
	unsigned long	sleep_time;
	size_t			eat_count;
}			t_config;

#endif
