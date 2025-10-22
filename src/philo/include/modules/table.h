/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:37:54 by yademirk          #+#    #+#             */
/*   Updated: 2025/09/23 21:02:20 by yademirk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef TABLE_H
# define TABLE_H

# include <structs/s_table.h>

int		init_table(t_table *table, int argc, char **argv);
void	clear_table(t_table *table);

#endif
