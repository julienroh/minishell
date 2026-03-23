/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 13:15:50 by haoky             #+#    #+#             */
/*   Updated: 2026/03/23 10:14:11 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Display the id and value of the env struct only if they have their printable
register as 1.
*/

int	exec_env(t_env *env, char **args)
{
	// t_env	*tmp;

	// tmp = env;
	// if (args[1] != NULL)
	// {
	// 	ft_putstr_fd("minishell : ", 2);
	// 	ft_putstr_fd("env: too many arguments\n", 2);
	// 	return (1);
	// }
	// while (tmp)
	// {
	// 	if (tmp->printable == 1)
	// 		printf("%s=%s\n", tmp->id, tmp->value);
	// 	tmp = tmp->next;
	// }
	// return (0);
	(void)args;
	t_env	*current;

	current = env;
	while (current)
	{
		printf("id = %s, value = %s, printable = %d\n", current->id, current->value, current->printable);
		current = current->next;
	}
	return (0);
}
