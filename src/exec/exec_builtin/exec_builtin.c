/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:31:11 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/12 11:54:29 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin is_builtin(char *exec_argv)
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
	return (CMD);
}
void	find_builtin_and_exec(t_data *data, char **args, t_builtin type_builtin)
{
	if (type_builtin == 0)
		exec_cd(data, args);
	else if (type_builtin == 1)
		exec_pwd(data->env);
	else if (type_builtin == 2)
		exec_export(data, args, 0);
	else if (type_builtin == 3)
		exec_env(data->env);
	else if (type_builtin == 4)
		exec_echo(data, args);
	else if (type_builtin == 5)
		exec_unset(args, &data->env);
	else if (type_builtin == EXIT)
		exec_exit(data);
}

int	exec_builtin_parent(t_data *data, char **exec_cmd)
{
	t_builtin	type_builtin;

	type_builtin = is_builtin(exec_cmd[0]);
	find_builtin_and_exec(data, exec_cmd, type_builtin);
	return (0);
}
