/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:14:40 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/13 17:49:42 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_tmpname(char **foldername, int counter)
{
	char	*num;

	if (counter == INT_MAX)
	{
		ft_putstr_fd("error : too much heredocs" , 2);
		return ;
	}
	num = ft_itoa(counter);
	if (check_malloc_ok(num) == -1)
		return ;
	*foldername = ft_strjoin("/tmp/minishell_tmp_", num);
	free(num);
	return ;
}

static void	heredoc_child_getinput(t_data *data, t_redir *r, int fd, char *name)
{
	char	*line;

	line = NULL;
	signal_heredoc();
	while (1)
	{
		errno = 0;
		line = readline("> ");
		if (g_sig == SIGINT)
			heredoc_sigint_cleanup(fd, name, data);
		if (!line)
			heredoc_cleanup_str(data, fd, name);
		if (is_delim(line, r->target))
			heredoc_delim_cleanup(fd, line, name, data);
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
	}
		free(name);
		name = NULL;
}

static int heredoc_waitpid(t_data *data, char *name, int status)
{
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		data->last_status = 130;
		unlink(name); 
		free(name);
		return (-1);
	}
	return (0);
}

int		prepare_all_heredocs(t_data *data)
{
	t_redir		*cur_redir;
	t_command	*cur_cmd;
	int	counter;

	counter = 0;
	cur_cmd = data->cmd_table;
	while (cur_cmd)
	{
		cur_redir = cur_cmd->redirs;
		while (cur_redir)
		{
			if (cur_redir->type == R_HEREDOC)
			{
				cur_redir->was_heredoc = 1;
				if (handle_heredoc(data, cur_redir, counter) == -1)
					return (-1);
				counter++;
			}
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
	return (0);
}

int	handle_heredoc(t_data *data, t_redir *r, int counter)
{
	int		fd;
	char	*name;
	int		pid;
	int		status;

	g_sig = 0;
	name = NULL;
	ft_tmpname(&name, counter);
	if (name == NULL)
		return (data->last_status = 1, -1);
	fd = open(name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600); // loop si o_excl est vrai ?
	if (fd < 0)
		return (data->last_status = 1, free(name), perror("open"), -1); //fontion d'erreur ?
	pid = safe_fork();
	if (pid < 0)
		return (data->last_status = 1, close(fd), unlink(name), free(name), -1); //fonction d'erreur ? print qqch ?
	if (pid == 0)
		heredoc_child_getinput(data , r, fd, name);
	close(fd);
	waitpid(pid, &status, 0);
	if (heredoc_waitpid(data, name, status) == -1)
		return (-1);
	if (heredoc_success_change_redirtype(r, data, name) == -1)
		return (-1);
	return (0);
}
