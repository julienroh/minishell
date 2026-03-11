/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:21:22 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/11 21:48:38 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multi_init_path_envp_cmd(t_command *cmd, t_data *data, char ***envp, char **path)
{
	int code;
	
	*envp = NULL;
	*path = NULL;
	*envp = env_to_envp(data->env);
	if (!*envp)
	{
		perror("malloc");
		exit(1);
	}
	code = ft_findpath(path, cmd->argv[0], *envp);
	if (code != 0)
	{
		if (!ft_strchr(cmd->argv[0], '/'))
		{
			print_error(cmd->argv[0]);
			print_error(": command not found\n");
			free_envp_path(*envp, *path);
			exit(code);
		}
		perror(cmd->argv[0]);
		free_envp_path(*envp, *path);
		exit(code);
	}
}

/* redirige l'output sur la pipe + close la partie lecture de la pipe.
*/
static void	redir_pipe_stdout(int pipefd[2])
{
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[1]);
		perror("dup2");
		exit (1);
	}
}

/* redirige l'input sur la pipe d'avant */
static void	redir_pipe_stdin(int pipefd[2])
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		perror("dup2");
		exit (1);
	}
}
/* close all pipes ! we redirected them already when needed.*/
static void	close_all_pipes(t_multi *v)
{
	int	i;

	i = 0;
	while (i < v->n_cmd - 1)
	{
		close(v->pipefd[i][0]);
		close(v->pipefd[i][1]);
		i++;
	}
}

/* s'occupe de rediriger les sorties en fonction des pipes et d'ou 
on est dans l'exec des cmds.*/
void	child_setup_pipes(t_multi *v, int i)
{
	if (i == 0)
	{
		redir_pipe_stdout(v->pipefd[i]);
	}
	else if (i > 0 && i != v->n_cmd - 1)
	{
		redir_pipe_stdin(v->pipefd[i - 1]);
		redir_pipe_stdout(v->pipefd[i]);
	}
	else if (i == v->n_cmd - 1)
	{
		redir_pipe_stdin(v->pipefd[i - 1]);
	}
	close_all_pipes(v);
}
