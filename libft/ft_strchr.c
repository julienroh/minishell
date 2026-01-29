/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:59:12 by haoky             #+#    #+#             */
/*   Updated: 2025/10/03 15:20:10 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
		{
			return (str + i);
		}
		i++;
	}
	if (str[i] == (char)c)
		return (str + i);
	return (NULL);
}
// int	main(void)
// {
// 	char s[] = "tripouille";
// 	printf("%s", ft_strchr(s, 0));
// }
