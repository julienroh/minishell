/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:15:19 by haoky             #+#    #+#             */
/*   Updated: 2026/01/23 15:06:37 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(char **args, t_env **env)
{
	int		i;
	t_env	*cur;
	t_env	*prev;

	i = 0;
	while (args[i + 1])
	{
		cur = *env;
		prev = NULL;
		while (cur)
		{
			if (!ft_strncmp(cur->id, args[i + 1], ft_strlen(args[i + 1]))
				&& (ft_strlen(args[i + 1]) == ft_strlen(cur->id)))
			{
				if (prev)
					prev->next = cur->next;
				else
					*env = cur->next;
				free(cur->id);
				free(cur->value);
				free(cur);
				break ;
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
}
