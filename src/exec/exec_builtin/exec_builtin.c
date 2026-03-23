/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:31:11 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/23 11:09:22 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btn	is_builtin(char *exec_argv)
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
		return (B_ECHO);
	if (ft_strncmp(exec_argv, "unset", 6) == 0)
		return (UNSET);
	if (ft_strncmp(exec_argv, "exit", 6) == 0)
		return (EXIT);
	return (CMD);
}

static int	find_builtin_and_exec(t_data *data, char **args, t_btn type_builtin)
{
	int	result;

	result = 0;
	if (type_builtin == 0)
		result = exec_cd(data, args);
	else if (type_builtin == 1)
		result = exec_pwd();
	else if (type_builtin == 2)
		result = exec_export(data, args, 0, 0);
	else if (type_builtin == 3)
		result = exec_env(data->env, args);
	else if (type_builtin == 4)
		result = exec_echo(data, args);
	else if (type_builtin == 5)
		result = exec_unset(args, &data->env, 0);
	else if (type_builtin == EXIT)
		result = exec_exit(data, args);
	return (result);
}

int	exec_builtin_parent(t_data *data, char **exec_cmd)
{
	t_btn	type_builtin;

	type_builtin = is_builtin(exec_cmd[0]);
	return (find_builtin_and_exec(data, exec_cmd, type_builtin));
}
