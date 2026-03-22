/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_no_env_underscore.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:30:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/22 18:26:23 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int create_path_underscore(t_data *data, char **argv)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (print_error_path(), 1);
	init_env_new_null(new);
	new->id = ft_strdup("_");
	if (!new->id)
		return (print_error_path(), free_single_env_node(new), 1);
	new->value = ft_strdup(argv[0]);
	if (!new->value)
		return (print_error_path(), free_single_env_node(new), 1);
	new->printable = 1;
	env_add_back(&data->env, new);
	return (0);
}
