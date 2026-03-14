/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:47:02 by yademirk          #+#    #+#             */
/*   Updated: 2026/03/14 20:20:22 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Converts the given string to a long integer.
 *
 * Additionally checks an optional sign character at the start of the string.
 *
 * @note You can't safely determine if the given string contains invalid
 * characters since this function simply returns 0 on such cases.
 */
long long	ft_atol(const char *str)
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
