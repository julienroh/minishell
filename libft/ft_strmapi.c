/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:41:09 by haoky             #+#    #+#             */
/*   Updated: 2025/10/04 12:55:30 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*to_return;
	size_t			size;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	to_return = malloc(size + 1);
	if (!to_return)
		return (NULL);
	while (s[i])
	{
		to_return[i] = f(i, s[i]);
		i++;
	}
	to_return[i] = '\0';
	return (to_return);
}
