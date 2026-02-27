/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:40:14 by haoky             #+#    #+#             */
/*   Updated: 2026/02/27 09:13:18 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_env(t_env *env)
// {
// 	t_env	*tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		printf("id = : %s && value = : %s && printable = : %d\n", 
// 		tmp->id, tmp->value, tmp->printable);
// 		tmp = tmp->next;
// 	}
// }

/*Fonction that test if the first arg is one of the command that we have
to handle. if that's the case, we enter in exec functions.
*/

int	analyze_args(t_data *data)
{
	if (ft_strncmp(data->args[0], "exit", 4) == 0 && ft_strlen(data->args[0]) == 4)
		return (0);
	else if (ft_strncmp(data->args[0], "pwd", 3) == 0 && ft_strlen(data->args[0]) == 3)
		exec_pwd(data->env);
	else if (ft_strncmp(data->args[0], "cd", 2) == 0 && ft_strlen(data->args[0]) == 2)
		exec_cd(data);
	else if (ft_strncmp(data->args[0], "echo", 4) == 0 && ft_strlen(data->args[0]) == 4)
		exec_echo(data);
	else if (ft_strncmp(data->args[0], "export", 6) == 0 && ft_strlen(data->args[0]) == 6)
		exec_export(data);
	else if (ft_strncmp(data->args[0], "unset", 5) == 0 && ft_strlen(data->args[0]) == 5)
		exec_unset(data->args, &data->env);
	else if (ft_strncmp(data->args[0], "env", 3) == 0 && ft_strlen(data->args[0]) == 3)
		exec_env(data->env);
	else
		exec_pot_export(data);
	return (1);
}
