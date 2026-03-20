/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_no_env_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:14:04 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/20 13:04:19 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_error_init_pwd(void)
{
	ft_putstr_fd("pwd: error retrieving current directory: getcwd: ", 2);
	ft_putstr_fd("cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
}
int	create_pwd(t_data *data)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		ft_putstr_fd("minishell : ", 2);
		perror("malloc");
		return (1);
	}
	new->id = ft_strdup("PWD");
	if (!new->id)
	{
		ft_putstr_fd("minishell : ", 2);
		perror("malloc");
		return (1);
	}
	new->value = getcwd(NULL, 0);
	if (!new->value)
	{
		print_error_init_pwd();
		return (1);
	}
	new->printable = 1;
	env_add_back(&data->env, new);
	return (0);
}
