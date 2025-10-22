/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:47:02 by yademirk          #+#    #+#             */
/*   Updated: 2025/09/04 15:51:31 by yademirk         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

long long	ft_atol(char *str)
{
	long long	total;
	char		sign;

	total = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		total = (total * 10) + (*str - '0');
		str++;
	}
	return (total * sign);
}
