/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:35:05 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/16 15:19:53 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_success_change_redirtype(t_redir *r, t_data *data, char *name)
{
	free(r->target);
	r->target = ft_strdup(name);
	if (!r->target)
	{
		ft_putstr_fd("minishell : ", 2);
		return (perror("malloc"), data->last_status = 1, free(name), -1);
	}
	free(name);
	r->type = R_IN;
	data->last_status = 0;
	return (0);
}

void	heredoc_sigint_cleanup(int fd, char *name, t_data *data)
{
	close(fd);
	free(name);
	free_all(data);
	g_sig = 0;
	exit(130);
}

void	heredoc_delim_cleanup(int fd, char *line, char *name, t_data *data)
{
	close (fd);
	free(line);
	free(name);
	free_all(data);
	exit(0);
}

int	is_delim(char *line, char *delim)
{
	int	len;

	len = ft_strlen(delim);
	return (ft_strncmp(line, delim, len + 1) == 0);
}

void	cleanup_tmpfiles_heredocs(t_data *data)
{
	t_redir		*cur_redir;
	t_com	*cur_cmd;

	cur_cmd = data->cmd_table;
	while (cur_cmd)
	{
		cur_redir = cur_cmd->redirs;
		while (cur_redir)
		{
			if (cur_redir->was_heredoc == 1)
			{
				if (unlink(cur_redir->target) == -1)
					perror("unlink");
			}
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
	return ;
}
