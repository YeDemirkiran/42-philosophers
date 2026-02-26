/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:45:04 by yademirk          #+#    #+#             */
/*   Updated: 2026/02/26 15:09:59 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_ROUTINE_H
# define PHILOSOPHERS_ROUTINE_H

# include <structs/s_philosopher.h>

void	philosopher_die(t_philosopher *philo, long time);
void	philosopher_eat(t_philosopher *philo);
void	philosopher_sleep(t_philosopher *philo);

#endif
