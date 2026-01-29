/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:46:24 by haoky             #+#    #+#             */
/*   Updated: 2025/10/04 12:48:19 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*to_return;

	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	to_return = malloc (size + 1);
	if (!to_return)
		return (NULL);
	while (s1[i])
	{
		to_return[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		to_return[i + j] = s2[j];
		j++;
	}
	to_return[i + j] = '\0';
	return (to_return);
}
// int	main(void)
// {
// 	char	*s1 = "Le LHC va ";
// 	char	*s2 = "faire match nul.";
// 	printf("%s\n", ft_strjoin(s1, s2));
// 	return (0);
// }
