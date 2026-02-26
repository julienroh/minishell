/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 13:15:50 by haoky             #+#    #+#             */
/*   Updated: 2026/02/26 14:00:08 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Display the id and value of the env struct only if they have their printable
register as 1.
*/

void	exec_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->printable == 1)
			printf("%s=%s\n", tmp->id, tmp->value);
		tmp = tmp->next;
	}
}
