/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 09:20:38 by jroh              #+#    #+#             */
/*   Updated: 2025/10/06 12:48:21 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *s, char c)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			result++;
		i++;
	}
	return (result);
}

int	size_word(const char *s, char c, int i)
{
	int	result;

	result = 0;
	while (s[i + result] && s[i + result] != c)
		result++;
	return (result);
}

void	copy_word(char *dest, const char *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i + j] && s[i + j] != c)
	{
		dest[j] = s[i + j];
		j++;
	}
	dest[j] = '\0';
}

char	**ft_split(const char *s, char c)
{
	char	**to_return;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	to_return = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!to_return)
		return (0);
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			size = size_word(s, c, i);
			to_return[j] = malloc(size + 1);
			if (!to_return[j])
				return (0);
			copy_word(to_return[j], s, c, i);
			j++;
		}
		i++;
	}
	to_return[j] = 0;
	return (to_return);
}
