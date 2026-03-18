/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 13:15:50 by haoky             #+#    #+#             */
/*   Updated: 2026/03/18 12:28:52 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Display the id and value of the env struct only if they have their printable
register as 1.
*/

int	exec_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->printable == 1)
			printf("%s=%s\n", tmp->id, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
