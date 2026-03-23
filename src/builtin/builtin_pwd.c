/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:52:08 by haoky             #+#    #+#             */
/*   Updated: 2026/03/22 19:48:16 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*search pwd with getcwd. Print error if getcwd failed.*/

int	exec_pwd(void)
{
	char	*result;

	result = NULL;
	result = getcwd(NULL, 0);
	if (!result)
	{
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return (1);
	}
	printf("%s\n", result);
	free(result);
	result = NULL;
	return (0);
}
