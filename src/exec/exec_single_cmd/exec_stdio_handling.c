/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stdio_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:15:13 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/08 13:54:58 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_stdio(t_stdio *stdio)
{
	stdio->saved_stdin = dup(STDIN_FILENO);
	if (stdio->saved_stdin == -1)
		return (-1);
	stdio->saved_stdout = dup(STDOUT_FILENO);
	if (stdio->saved_stdout == -1)
		return (close(stdio->saved_stdin), -1);
	return (0);
}

int	restore_stdio(t_stdio *stdio)
{
	if (dup2(stdio->saved_stdin, STDIN_FILENO) == -1)
		return (-1);
	if (dup2(stdio->saved_stdout, STDOUT_FILENO) == -1)
		return (-1);
	close(stdio->saved_stdin);
	close(stdio->saved_stdout);
	stdio->saved_stdin = -1;
	stdio->saved_stdout = -1;
	return (0);
}
