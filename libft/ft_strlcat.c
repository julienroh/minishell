/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:18:55 by haoky             #+#    #+#             */
/*   Updated: 2025/10/03 14:33:14 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	i = 0;
	dlen = ft_strlen((char *)dest);
	slen = ft_strlen((char *)src);
	if (size <= dlen)
		return (size + slen);
	while (src[i] && ((dlen + i) < (size - 1)))
	{
		dest[dlen + i] = src[i];
		i++;
	}
	dest[dlen + i] = '\0';
	return (dlen + slen);
}

// int	main(void)
// {
// 	char	src[] = "World!";
// 	char	dest[20] = "Hello ";

// 	size_t	result = ft_strlcat(dest, src, 9);

// 	printf("%s\n", dest);
// 	printf("%ld\n", result);
// }
