/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:19:06 by haoky             #+#    #+#             */
/*   Updated: 2026/01/24 17:19:54 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_identifier(char *arg)
{
	char	*find_equal;
	char	*to_return;
	size_t	len_id;
	int		i;

	i = 0;
	find_equal = ft_strchr(arg, '=');
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (ft_substr(arg, 0, i + 2));
		i++;
	}
	if (!find_equal)
		return (ft_strdup(arg));
	len_id = find_equal - arg;
	to_return = malloc(sizeof(char) * (len_id + 1));
	if (!to_return)
		return (NULL);
	ft_strlcpy(to_return, arg, len_id + 1);
	return (to_return);
}

char	*get_value(char *arg)
{
	char	*find_equal;

	find_equal = ft_strchr(arg, '=');
	if (!find_equal)
		return (NULL);
	return (ft_strdup(find_equal + 1));
}
