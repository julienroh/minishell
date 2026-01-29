/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 13:14:39 by haoky             #+#    #+#             */
/*   Updated: 2026/01/11 16:13:59 by haoky            ###   ########.fr       */
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

void	exec_echo(char **args)
{
	int	size_arg;

	size_arg = ft_strlen(args[1]);
	if (args[1][0] == '"' && args[1][size_arg - 1] == '"')
	{
		printf("oui\n");
		args[1] = ft_substr(args[1], 1, size_arg - 2);
	}
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
}
