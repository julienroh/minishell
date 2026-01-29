/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:17:47 by haoky             #+#    #+#             */
/*   Updated: 2025/12/02 11:36:24 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb <= 0 || size <= 0)
		return (malloc(0));
	if (nmemb > 65535 || size > 65535)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset((unsigned char *)ptr, 0, nmemb * size);
	return (ptr);
}

// int	main(void)
// {
// 	int	x = 2147483647;
// 	int	y = 2147483647;
// 	printf("%p", ft_calloc(x, y));
// 	return (0);
// }
