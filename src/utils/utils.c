/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:32:06 by haoky             #+#    #+#             */
/*   Updated: 2026/03/23 12:45:15 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	define_size(t_env *env)
{
	int		i;
	t_env	*current;

	i = 0;
	current = env;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}

int	is_redir(t_token *tok)
{
	if (tok->type == 2 || tok->type == 3 || tok->type == 4 || tok->type == 5)
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	size_env(t_env *env)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}
