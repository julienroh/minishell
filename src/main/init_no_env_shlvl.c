/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_no_env_shlvl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:09:33 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/20 14:28:32 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_shlvl(void)
{
	ft_putstr_fd("minishell : ", 2);
	perror("malloc");
}

int	create_shlvl(t_data *data)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		print_error_shlvl();
		return (1);
	}
	new->id = ft_strdup("SHLVL");
	if (!new->id)
	{
		print_error_shlvl();
		return (1);
	}
	new->value = ft_strdup("1");
	if (!new->value)
	{
		print_error_shlvl();
		return (1);
	}
	new->printable = 1;
	env_add_back(&data->env, new);
	return (0);
}

void	incr_shlvl(t_env *env)
{
	t_env	*cur;
	int		old_value;

	cur = env;
	while(cur)
	{
		if (ft_strncmp(cur->id , "SHLVL", 5) == 0)
		{
			old_value = ft_atoi(cur->value);
			old_value++;
			free(cur->value);
			cur->value = NULL;
			cur->value = ft_itoa(old_value);
			if (!cur->value)
				return (print_error_shlvl());
			return ;
		}
		cur = cur->next;
	}
}
