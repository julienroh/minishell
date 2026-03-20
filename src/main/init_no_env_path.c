/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_no_env_bin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:30:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/20 12:50:48 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_path(void)
{
	ft_putstr_fd("minishell : ", 2);
	perror("malloc");
}

int create_path(t_data *data, char **argv)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		print_error_path();
		return (1);
	}
	new->id = ft_strdup("_");
	if (!new->id)
	{
		print_error_path();
		return (1);
	}
	new->value = ft_strdup(argv[0]);
	if (!new->value)
	{
		print_error_path();
		return (1);
	}
	new->printable = 1;
	env_add_back(&data->env, new);
	return (0);
}
