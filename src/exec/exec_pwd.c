/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:52:08 by haoky             #+#    #+#             */
/*   Updated: 2026/02/07 12:03:41 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*We look through the env struct if we see the id called PWD and display the
value.
*/

int	exec_pwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->id, "PWD", ft_strlen(tmp->id)))
		{
			printf("%s\n", tmp->value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
