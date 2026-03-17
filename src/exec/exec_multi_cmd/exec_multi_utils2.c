/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:21:22 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/17 13:25:09 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*alloue env en format char **. en cas d'erreur, free data, v, exit. */

void	multi_init_envp(t_data *data, t_multi *v, char ***envp)
{
	*envp = NULL;
	*envp = env_to_envp(data->env);
	if (!*envp)
	{
		print_error("minishell : ");
		perror("malloc");
		free_exit_wrapper_child(data, v, 1);
	}
}

/* redirige l'output sur la pipe + close la partie lecture de la pipe. 
free et exit si err */

static void	redir_pipe_stdout(int pipefd[2], t_multi *v, t_data *data)
{
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close_all_pipes(v);
		free_exit_wrapper_child(data, v, 1);
	}
}

/* redirige l'input sur la pipe d'avant, free et exit si err */

static void	redir_pipe_stdin(int pipefd[2], t_multi *v, t_data *data)
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close_all_pipes(v);
		free_exit_wrapper_child(data, v, 1);
	}
}

/* s'occupe de rediriger les sorties en fonction des pipes et d'ou 
on est dans l'exec des cmds. si erreur, free tout et exit */

void	child_setup_pipes(t_multi *v, int i, t_data *data)
{
	if (i == 0)
	{
		redir_pipe_stdout(v->pipefd[i], v, data);
	}
	else if (i > 0 && i != v->n_cmd - 1)
	{
		redir_pipe_stdin(v->pipefd[i - 1], v, data);
		redir_pipe_stdout(v->pipefd[i], v, data);
	}
	else if (i == v->n_cmd - 1)
	{
		redir_pipe_stdin(v->pipefd[i - 1], v, data);
	}
	close_all_pipes(v);
}
