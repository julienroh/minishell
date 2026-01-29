/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:04:43 by haoky             #+#    #+#             */
/*   Updated: 2025/10/06 12:37:18 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_isset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_get_size(const char *s1, const char *set)
{
	size_t	count;
	size_t	size;

	size = ft_strlen(s1);
	count = 0;
	while (ft_isset(s1[size - count - 1], set))
		count++;
	return (size - count);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	len;

	len = ft_strlen(s1);
	start = 0;
	end = len - 1;
	while (s1[start] && (ft_strchr(set, s1[start]) != 0))
		start++;
	while (start < end && (ft_strrchr(set, s1[end]) != 0))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}

// int	main(void)
// {
// 	char	*s1 = "abcdba";
// 	char	*set = "acb";
// 	printf("%s", ft_strtrim(s1, set));
// 	return (0);
// }
