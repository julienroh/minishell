/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:15:19 by haoky             #+#    #+#             */
/*   Updated: 2026/03/17 15:42:29 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Erase id int the env sutruct.
*/

static void	free_cur(t_env *cur)
{
	free(cur->id);
	free(cur->value);
	free(cur);
}

int	exec_unset(char **args, t_env **env, int i)
{
	t_env	*cur;
	t_env	*prev;

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
				free_cur(cur);
				break ;
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
	return (0);
}
