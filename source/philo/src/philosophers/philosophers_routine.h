/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:45:04 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/14 21:54:45 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_ROUTINE_H
# define PHILOSOPHERS_ROUTINE_H

# include <structs/s_philosopher.h>

/**
 * @brief Acquires the forks automatically and starts eating.
 *
 * Checks the death and dinner state before each important state
 * and self-terminates accordingly. Returns 0 on such cases, which means
 * the philosopher should stop and exit immediately.
 *
 * @return 0 on failure (death, dinner over), 1 on success.
 */
int		philosopher_eat(t_philosopher *philo);

/**
 * @brief Philosopher sleep routine. Sleeps with intervals.
 * Automatically stops if the philosopher has died or when the
 * dinner is over.
 */
void	philosopher_sleep(t_philosopher *philo);

#endif
