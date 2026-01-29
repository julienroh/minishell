/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:21:05 by haoky             #+#    #+#             */
/*   Updated: 2025/10/06 15:17:46 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = 0;
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			ptr = (char *)(s + i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		ptr = (char *)(s + i);
	return (ptr);
}
// int	main(void)
// {
// 	char s[] = "tripouille";
// 	char s2[] = "ltripouiel";
// 	char s3[] = "";
// 	printf("%s\n", strrchr(s3, 0));
// 	printf("%s\n", ft_strrchr(s3, 0));
// 	return (0);
// }
