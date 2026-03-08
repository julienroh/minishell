/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:41:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/07 12:49:39 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_if_valid(int fd)
{
	if (fd >= 0)
		close(fd);
}

pid_t	safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}

