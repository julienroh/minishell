/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:39:24 by jroh              #+#    #+#             */
/*   Updated: 2026/03/23 12:45:10 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_exit(char *str_1, char *str_2)
{
	ft_putstr_fd("minishell: exit: '", 2);
	ft_putstr_fd(str_1, 2);
	ft_putstr_fd("' ", 2);
	ft_putstr_fd(str_2, 2);
}

void	print_error_cd(char *str)
{
	ft_putstr_fd("minishell: cd: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': no such file or directory\n", 2);
}

void	print_error_export(char *str)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

t_env	*find_env(t_data *data, char *id)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->id, id, ft_strlen(id))
			&& ft_strlen(tmp->id) == ft_strlen(id))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	wraper_check_id(char *str, int *to_return)
{
	print_error_export(str);
	*to_return = 1;
}
