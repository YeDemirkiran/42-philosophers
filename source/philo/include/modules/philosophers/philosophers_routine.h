/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:45:04 by yademirk          #+#    #+#             */
/*   Updated: 2025/10/03 20:57:03 by yademirk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PHILOSOPHERS_ROUTINE_H
# define PHILOSOPHERS_ROUTINE_H

# include <structs/s_thread_data.h>

void	philosopher_die(t_thread_data *data);
void	philosopher_eat(t_thread_data *data);
void	philosopher_sleep(t_thread_data *data);

#endif
