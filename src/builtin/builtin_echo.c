/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 13:14:39 by haoky             #+#    #+#             */
/*   Updated: 2026/03/10 10:38:53 by mfumeaux         ###   ########.fr       */
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

void	exec_echo(t_data *data, char **args)
{
	if (!args[1])
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(args[1], "-n", ft_strlen(args[1])) != 0)
	{
		print_echo(args, 1, 0);
	}
	else
		print_echo(args, 2, 1);
	data->last_status = 0;
}
