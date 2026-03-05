/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:06:27 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/05 12:16:45 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *exec_argv)
{
	if (!exec_argv || !exec_argv[0])
		return (false);
	if (ft_strncmp(exec_argv, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(exec_argv, "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(exec_argv, "export", 7) == 0)
		return (true);
	if (ft_strncmp(exec_argv, "env", 4) == 0)
		return (true);
	if (ft_strncmp(exec_argv, "echo", 5) == 0)
		return (true);
	if (ft_strncmp(exec_argv, "unset", 6) == 0)
		return (true);
	if (ft_strncmp(exec_argv, "exit", 6) == 0)
		return (true);
	return(false);
}
