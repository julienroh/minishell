/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:06:27 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/10 10:11:07 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin is_builtin(char *exec_argv)
{
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

static int	find_builtin_and_exec(t_data *data, char **exec_cmd, t_builtin type_builtin)
{
	int	to_return;

	if (type_builtin == 0)
		to_return = exec_cd(data, args);
	else if (type_builtin == 1)
		to_return = exec_pwd(data->env);
	else if (type_builtin == 2)
		to_return = exec_export(data, args);
	else if (type_builtin == 3)
		to_return = exec_env(data->env);
	else if (type_builtin == 4)
		to_return = exec_echo(data, args);
	else if (type_builtin == 5)
		to_return = exec_unset(args, env)
	else if (type_builtin == 1)

		
}

int	exec_builtin_parent(t_data *data, char **exec_cmd)
{
	t_builtin	type_builtin;
	int			i = 0;

	type_builtin = is_builtin(exec_cmd[0]);
	find_builtin_and_exec(data, exec_cmd, type_builtin);
	return (0);
	//créer et adapté le format d'env en fonction du builtin ?
	//idée : transformer env en list, faire la cmd,
	// puis retransformer en envp(char**)
	//si besoin : return -1 error, 0 ok.



	//Est ce que je dois iterer sur exec_cmd tant que ce n'est pas autre chose
	//que CMD comme ca je fais le premier builtin croise ?

	//Est ce que je peux avoir plusieurs commandes ? Savoir si je dois prendre
	//dans le builtin que jusqu'a la prochaine commande ?
}

int	exec_external_cmd(t_data *data, t_exec_data *ctx)
{
	pid_t	pid;
	pid = safe_fork();
	if (pid == -1)
		return;
	if (pid == 0)
	{
		if (execve(ft_findpath(ctx->exec_argv[0]), ctx->exec_argv, ctx->envp) == -1)
		{
			perror("execve");
			data->last_status = 127;
		}
	}
	//close ?
	waitpid(pid, &data->last_status, 0);
	if (WIFEXITED(data->last_status))
		exit(WEXITSTATUS(data->last_status));
	if (WIFSIGNALED(data->last_status))
		exit(128 + WTERMSIG(data->last_status));
}
