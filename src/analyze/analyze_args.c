/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:40:14 by haoky             #+#    #+#             */
/*   Updated: 2026/02/07 12:01:35 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_env(t_env *env)
// {
// 	t_env	*tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		printf("id = : %s && value = : %s && printable = : %d\n", tmp->id, tmp->value, tmp->printable);
// 		tmp = tmp->next;
// 	}
// }

/*Fonction that test if the first arg is one of the command that we have
to handle. if that's the case, we enter in exec functions.
*/

int	analyze_args(char **args, t_env *env)
{
	if (ft_strncmp(args[0], "exit", 4) == 0 && ft_strlen(args[0]) == 4)
		return (0);
	else if (ft_strncmp(args[0], "pwd", 3) == 0 && ft_strlen(args[0]) == 3)
		exec_pwd(env);
	else if (ft_strncmp(args[0], "cd", 2) == 0 && ft_strlen(args[0]) == 2)
		exec_cd(args, env);
	else if (ft_strncmp(args[0], "echo", 4) == 0 && ft_strlen(args[0]) == 4)
		exec_echo(args);
	else if (ft_strncmp(args[0], "export", 6) == 0 && ft_strlen(args[0]) == 6)
		exec_export(args, env);
	else if (ft_strncmp(args[0], "unset", 5) == 0 && ft_strlen(args[0]) == 5)
		exec_unset(args, &env);
	else if (ft_strncmp(args[0], "env", 3) == 0 && ft_strlen(args[0]) == 3)
		exec_env(env);
	else
		exec_pot_export(args, env);
	//print_env(env);
	return (1);
}
