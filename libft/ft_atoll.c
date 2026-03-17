/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 18:17:21 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/01/28 18:23:01 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoll(char *str)
{
	long long	sign;
	long long	ret;

	sign = 1;
	ret = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		sign = 1 - (2 * (*str++ == '-'));
	while (*str >= '0' && *str <= '9')
		ret = ((ret * 10) + (*str++ - 48));
	return (ret * sign);
}
