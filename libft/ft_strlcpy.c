/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:53:32 by haoky             #+#    #+#             */
/*   Updated: 2025/10/06 15:03:55 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < (size - 1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}
// int	main(void)
// {
// 	char src[] = "coucou";
// 	char dest[10]; memset(dest, 'A', 10);
// 	printf("%ld\n", ft_strlcpy(dest, src, 2));
// 	printf("%c\n", dest[0]);
// 	printf("%c\n", dest[1]);
// 	printf("%c\n", dest[2]);
// 	return (0);
// }
