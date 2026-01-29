/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:42:40 by haoky             #+#    #+#             */
/*   Updated: 2025/10/06 12:45:13 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cut(char *str, int i, int n)
{
	while (i <= n)
	{
		i++;
	}
	str[i] = '\0';
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < n)
	{
		j = 0;
		if (haystack[i] == needle[0])
		{
			while (haystack[i + j] == needle[j] && (i + j) < n)
			{
				if (needle[j + 1] == '\0')
					return ((char *)haystack + i);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	//char haystack[30] = "aaabcabcd";
// 	//char needle[10] = "aabc";
// 	char * empty = (char*)"";
// 	printf("\n%s", strnstr(empty, "", -1));
// 	printf("\n%s", ft_strnstr(empty, "", -1));
// }
