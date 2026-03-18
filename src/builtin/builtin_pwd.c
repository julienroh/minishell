/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:52:08 by haoky             #+#    #+#             */
/*   Updated: 2026/03/18 17:56:25 by mfumeaux         ###   ########.fr       */
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
		ft_putstr_fd("cannot access parent directories: No such file or directory\n", 2);
		return (1);
	}
	ft_putstr_fd(result, 2);
	write(1, "\n", 1);
	free(result);
	result = NULL;
	return (0);
}
