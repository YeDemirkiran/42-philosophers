/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 18:21:55 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/16 18:27:12 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_MESSAGES_H
# define PHILO_MESSAGES_H

// Colors for reference

# define THINK_COLOR "\033[1;93m"
# define TAKE_FORK_COLOR "\033[1;37m"
# define EAT_COLOR "\033[1;92m"
# define SLEEP_COLOR "\033[1;96m"
# define DEATH_COLOR "\033[1;91m"
# define COLOR_RESET "\033[0m"

// We'll have to embed color codes directly in the macro, instead of
// being able to use the defined ones already.
// Thanks Norm ;)

# define EAT_MESSAGE "\033[1;92mis eating\033[0m\n"
# define THINK_MESSAGE "\033[1;93mis thinking\033[0m\n"
# define FORK_MESSAGE "\033[1;37mhas taken a fork\033[0m\n"
# define SLEEP_MESSAGE "\033[1;96mis sleeping\033[0m\n"
# define DEATH_MESSAGE "\033[1;91mdied\033[0m\n"

#endif
