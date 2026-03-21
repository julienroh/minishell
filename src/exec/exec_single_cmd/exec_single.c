/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:06:27 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/21 20:41:50 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_free_exit(t_data *data, int code)
{
	free_all(data);
	exit(code);
}

/*inside the fork, applies redirections,
 then check path, then init char **envp for execve*/
static void	exec_child(t_data *data)
{
	char	**envp;
	char	*path;
	int		code;

	envp = NULL;
	path = NULL;
	signal_exec();
	if (apply_redirections(data->cmd_table->redirs) == -1)
		single_free_exit(data, 1);
	single_init_envp(data, &envp);
	code = multi_init_path(data->cmd_table, envp, &path);
	if (code != 0)
		single_free_exit(data, code);
	if (execve(path, data->cmd_table->argv, envp) == -1)
		single_execve_error(data, envp, path);
}

//defensive fork, then exec child, then waitpid.

int	exec_external_cmd(t_data *data)
{
	pid_t	pid;
	int		wstatus;

	pid = safe_fork();
	if (pid == -1)
		return (data->last_status = 1, -1);
	if (pid == 0)
		exec_child(data);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		data->last_status = (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
	{
		data->last_status = (128 + WTERMSIG(wstatus));
		if (WTERMSIG(wstatus) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(wstatus) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
	}
	return (0);
}

/*if it's a builtin, exec in parent not child,
 with a redirected of stdio if needed.*/
int	exec_cmd(t_data *data)
{
	t_btn	type;
	t_stdio	stdio;

	type = is_builtin(data->cmd_table->argv[0]);
	if (type != CMD && type != EXIT)
	{
		if (wrapper_apply_redirs(data, &stdio) == -1)
			return (-1);
		data->last_status = exec_builtin_parent(data, data->cmd_table->argv);
		restore_stdio(&stdio);
		return (0);
	}
	else if (type == EXIT)
	{
		if (wrapper_apply_redirs(data, &stdio) == -1)
			return (-1);
		restore_stdio(&stdio);
		data->last_status = exec_builtin_parent(data, data->cmd_table->argv);
	}
	return (exec_external_cmd(data));
}

/* check for assign then exec command.
The assign is outside of minishell scope*/

int	exec_single_command(t_data *data)
{
	int	assign_count;

	assign_count = count_prefix_assignments(data->cmd_table->argv);
	if (data->cmd_table->argv[assign_count] == NULL)
	{
		if (handle_assignment_only_command(data, assign_count) == -1)
			return (data->last_status = 1, -1);
		return (data->last_status = 0);
	}
	exec_cmd(data);
	return (0);
}
