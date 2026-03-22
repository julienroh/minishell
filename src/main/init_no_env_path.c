/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_no_env_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 17:27:49 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/22 18:05:43 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_path(void)
{
	ft_putstr_fd("minishell : ", 2);
	perror("malloc");
}

void	init_env_new_null(t_env *new)
{
	new->id = NULL;
	new->next = NULL;
	new->value = NULL;
}

void	free_single_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->id)
		free(node->id);
	if (node->value)
		free(node->value);
	free(node);
}

int create_path(t_data *data)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (print_error_path(), 1);
	init_env_new_null(new);
	new->id = ft_strdup("PATH");
	if (!new->id)
		return (print_error_path(), free_single_env_node(new), 1);
	new->value = ft_strjoin("/usr/local/sbin:/usr/local/bin:",
			"/usr/sbin:/usr/bin:/sbin:/bin:");
	if (!new->value)
		return (print_error_path(), free_single_env_node(new), 1);
	new->printable = 1;
	env_add_back(&data->env, new);
	return (0);
}
