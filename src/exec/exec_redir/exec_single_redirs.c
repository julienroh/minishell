/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:32:46 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/13 17:48:54 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_fd(t_redir *redirs)
{
	if (redirs->type == R_IN)
		return (open(redirs->target, O_RDONLY));
	if (redirs->type == R_OUT)
		return (open(redirs->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redirs->type == R_APPEND)
		return (open(redirs->target, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

static int	redir_dup2(t_redir *redirs, int fd)
{
	if (redirs->type == R_IN)
		return (dup2(fd, STDIN_FILENO));
	if (redirs->type == R_OUT || redirs->type == R_APPEND)
		return (dup2(fd, STDOUT_FILENO));
	return (-1);
}

int	apply_redirections(t_redir *redirs)
{
    t_redir	*tmp;
	int 	fd;
	
	tmp = redirs;
	while(tmp)
	{
		if (!tmp->target)
			return (-1);
		if (tmp->type == R_HEREDOC)
			return (-1);
		fd = open_redir_fd(tmp);
		if (fd == -1)
			return (perror(tmp->target), -1);
		if (redir_dup2(tmp, fd) == -1)
			return (perror("dup2"), close(fd), -1);
		close(fd);
		tmp = tmp->next;
	}
	return (0);
}

int	wrapper_apply_redirs(t_data *data, t_stdio *stdio)
{
	if (save_stdio(stdio) == -1)
		return (data->last_status = 1, -1);
	if (apply_redirections(data->cmd_table->redirs) == -1)
		return (restore_stdio(stdio), data->last_status = 1, -1);
	return (0);
}
