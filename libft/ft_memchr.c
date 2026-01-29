/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:05:20 by haoky             #+#    #+#             */
/*   Updated: 2025/10/03 14:41:00 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == ((unsigned char)c))
			return ((void *)str + i);
		i++;
	}
	return (NULL);
}
// int	main(void)
// {
// 	char s[] = {0, 1, 2 ,3 ,4 ,5};
// 	ft_memchr(s, 0, 1);
// 	printf ("%c\n", s[1]);
// 	return (0);
// }
