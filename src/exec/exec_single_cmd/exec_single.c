/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:06:27 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/09 00:16:51 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin is_builtin(char *exec_argv)
{
	//add acceptation pour majuscule aussi : cd ou CD, pwd ou PWD ...
	//pour pipeline -> cd/export/unset/exit ->exec parent.
	if (!exec_argv || !exec_argv[0])
		return (CMD);
	if (ft_strncmp(exec_argv, "cd", 3) == 0)
		return (CD);
	if (ft_strncmp(exec_argv, "pwd", 4) == 0)
		return (PWD);
	if (ft_strncmp(exec_argv, "export", 7) == 0)
		return (EXPORT);
	if (ft_strncmp(exec_argv, "env", 4) == 0)
		return (ENV);
	if (ft_strncmp(exec_argv, "echo", 5) == 0)
		return (ECHO);
	if (ft_strncmp(exec_argv, "unset", 6) == 0)
		return (UNSET);
	if (ft_strncmp(exec_argv, "exit", 6) == 0)
		return (EXIT);
	return(CMD);
}
/* 

*/
void	init_path_envp_cmd(t_data *data, char ***envp, char **path)
{
	int code;
	
	*envp = NULL;
	*path = NULL;
	*envp = env_to_envp(data->env);
	if (!envp)
	{
		perror("malloc");
		exit(1);
	}
	code = ft_findpath(path, data->cmd_table->argv[0], *envp);
	if (code != 0)
	{
		if (!ft_strchr(data->cmd_table->argv[0], '/'))
		{
			print_error(data->cmd_table->argv[0]);
			print_error(": command not found\n");
			free_envp_path(*envp, *path);
			exit(code);
		}
		perror(data->cmd_table->argv[0]);
		free_envp_path(*envp, *path);
		exit(code);
	}
}

static void exec_child(t_data *data)
{
	char 	**envp;
	char	*path;

	init_path_envp_cmd(data, &envp, &path);
	if (apply_redirections(data->cmd_table->redirs) == -1)
	{
		free_envp_path(envp, path);
		exit(1);
	}
	if (execve(path, data->cmd_table->argv, envp) == -1)
	{	
		perror(data->cmd_table->argv[0]);
		free_envp_path(envp, path);
		exit(127);
	}
}

int	exec_external_cmd(t_data *data)
{
	pid_t	pid;
	int		wstatus;

	pid = safe_fork();
	if (pid == -1)
		return (data->last_status = 1, -1);
	if (pid == 0)
		exec_child(data); //ici, va falloir fix findpath et exit status dans initpath.
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		data->last_status = (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		data->last_status = (128 + WTERMSIG(wstatus));
	return (0);
} 

int	exec_builtin_parent(t_data *data, t_builtin type)
{
	if (type == EXIT)
		exit(0);
	data->last_status = 1;
	return(printf("builtin exec dans le parent\n"), 1);
}
int	exec_cmd(t_data *data)
{
	t_builtin	type;
	t_stdio		stdio;

	type = is_builtin(data->cmd_table->argv[0]);
	if (type != CMD)
	{
		if (wrapper_apply_redirs(data, &stdio) == -1)
			return (-1);
		data->last_status = exec_builtin_parent(data, type);
		restore_stdio(&stdio);
		return(0);
	}
	return (exec_external_cmd(data));
}

int	exec_single_command(t_data *data)
{
	int	assign_count;

	assign_count = count_prefix_assignments(data->cmd_table->argv);
	if(data->cmd_table->argv[assign_count] == NULL)
	{
		if (handle_assignment_only_command(data, assign_count) == -1)
			return(data->last_status = 1, -1);
		return (data->last_status = 0);
	}
	exec_cmd(data);
	//free la char** env si pas deja fait.
	return (0);
}
