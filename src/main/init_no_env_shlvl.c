/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_no_env_shlvl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:09:33 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/22 18:25:02 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_shlvl(t_data *data)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (print_error_path(), 1);
	init_env_new_null(new);
	new->id = ft_strdup("SHLVL");
	if (!new->id)
		return (print_error_path(), free_single_env_node(new), 1);
	new->value = ft_strdup("1");
	if (!new->value)
		return (print_error_path(), free_single_env_node(new), 1);
	new->printable = 1;
	env_add_back(&data->env, new);
	return (0);
}

void	incr_shlvl(t_env *env)
{
	t_env	*cur;
	int		old_value;
	char	*new_value;

	new_value = NULL;
	cur = env;
	while(cur)
	{
		if (ft_strncmp(cur->id , "SHLVL", 5) == 0)
		{
			old_value = ft_atoi(cur->value);
			old_value++;
			new_value = ft_itoa(old_value);
			if (!new_value)
				return (ft_putstr_fd("minishell : malloc error while incremented SHLVL\n", 2));
			free(cur->value);
			cur->value = new_value;
			return ;
		}
		cur = cur->next;
	}
}
