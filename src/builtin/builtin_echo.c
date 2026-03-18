/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 13:14:39 by haoky             #+#    #+#             */
/*   Updated: 2026/03/18 12:32:51 by mfumeaux         ###   ########.fr       */
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

/* check for -n options in echo */
static int	check_option(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '-' && args[i][j + 1] == 'n')
		{
			j++;
			while (args[i][j])
			{
				if (args[i][j] == 'n')
					j++;
				else
					return (i);
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}

/*If there is the option "-n" after echo, we have to not put the "\n" after
the execution of echo.
*/
int	exec_echo(t_data *data, char **args)
{
	int	i;

	(void)data;
	i = 0;
	if (!args[1])
	{
		printf("\n");
		return (0);
	}
	i = check_option(args);
	if (i == 1)
		print_echo(args, i, 0);
	else
		print_echo(args, i, 1);
	return (0);
}
