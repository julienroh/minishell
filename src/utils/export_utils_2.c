/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:19:06 by haoky             #+#    #+#             */
/*   Updated: 2026/02/26 14:00:08 by jroh             ###   ########.fr       */
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
	{
		
	}
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

int	max(char *arg_a, char *arg_b)
{
	int	count_a;
	int	count_b;
	int	i;

	count_a = 0;
	count_b = 0;
	i = 0;
	while (arg_a[i])
	{
		count_a++;
		i++;
	}
	i = 0;
	while (arg_b[i])
	{
		count_b++;
		i++;
	}
	if (count_a >= count_b)
		return (count_a);
	else
		return (count_b);
}

void	swap(char **arg_a, char **arg_b)
{
	char	*tmp;

	tmp = *arg_a;
	*arg_a = *arg_b;
	*arg_b = tmp;
}

void	free_char_env(char **char_env)
{
	int	i;

	i = 0;
	while (char_env[i])
	{
		free(char_env[i]);
		i++;
	}
}
