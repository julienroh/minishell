/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 09:53:30 by jroh              #+#    #+#             */
/*   Updated: 2025/10/06 14:59:44 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intsize(int n)
{
	int			count;
	long int	nb;

	count = 1;
	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		count++;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int			size;
	int			i;
	long int	nb;
	char		*arr;

	nb = n;
	i = 1;
	size = ft_intsize(nb);
	arr = malloc(size + 1);
	if (!arr)
		return (NULL);
	if (nb < 0)
	{
		arr[0] = '-';
		nb = -nb;
	}
	while (nb > 9)
	{
		arr[size - i] = (nb % 10) + '0';
		nb = nb / 10;
		i++;
	}
	arr[size - i] = nb + '0';
	arr[size] = '\0';
	return (arr);
}
