/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 13:14:39 by haoky             #+#    #+#             */
/*   Updated: 2026/03/17 14:21:23 by haoky            ###   ########.fr       */
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

int	exec_echo(t_data *data, char **args)
{
	(void)data;
	if (!args[1])
	{
		printf("\n");
		return (0);
	}
	if (ft_strncmp(args[1], "-n", ft_strlen(args[1])) != 0)
	{
		print_echo(args, 1, 0);
	}
	else
		print_echo(args, 2, 1);
	return (0);
}
