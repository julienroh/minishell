/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:26:38 by jroh              #+#    #+#             */
/*   Updated: 2025/10/06 10:56:43 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*copie;
	char	*str;

	str = (char *)s;
	i = 0;
	copie = malloc(ft_strlen(str) + 1);
	if (!copie)
		return (NULL);
	while (str[i])
	{
		copie[i] = str[i];
		i++;
	}
	copie[i] = '\0';
	return (copie);
}
// int	main(void)
// {
// 	char	str[] = "Hello World!";
// 	char	*copie;s
// 	copie = ft_strdup(str);
// 	printf("%s", copie);
// 	return (0);
// }