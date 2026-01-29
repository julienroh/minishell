/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:19:10 by haoky             #+#    #+#             */
/*   Updated: 2025/10/06 15:02:23 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	if (src == 0 && dest == 0)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
// int	main(void)
// {
// 	size_t	n = 5;
// 	char	*src = "Hello, World!";
// 	char	dest1[20];
// 	char	dest2[20];
// 	memcpy(dest2, src, n);
// 	ft_memcpy(dest1, src, n);
// 	printf ("%s", dest1);
// 	printf ("%s", dest2);
// }
