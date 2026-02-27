/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 13:14:39 by haoky             #+#    #+#             */
/*   Updated: 2026/02/27 09:13:52 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(char **args, int i, int n)
{
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i] != 0)
			printf(" ");
	}
	if (n != 1)
		printf("\n");
}

/*If there is the option "-n" after echo, we have to not put the "\n" after
the execution of echo.
*/

void	exec_echo(t_data *data)
{
	if (!data->args[1])
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(data->args[1], "-n", ft_strlen(data->args[1])) != 0)
	{
		print_echo(data->args, 1, 0);
	}
	else
		print_echo(data->args, 2, 1);
}
