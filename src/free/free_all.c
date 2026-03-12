/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:07:18 by jroh              #+#    #+#             */
/*   Updated: 2026/03/12 11:39:55 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_data *data)
{
	free_data_except_env(data);
	free_env(data->env);
}

void	free_all_malloc(t_data *data)
{
	free_data_except_env(data);
	free_env(data->env);
	perror("malloc\n");
	exit(1);
}
