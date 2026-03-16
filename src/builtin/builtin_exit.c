/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:08:35 by jroh              #+#    #+#             */
/*   Updated: 2026/03/16 23:08:20 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(t_data *data, char **args)
{
	if (args && data)
		exit(0);
	// if (args[2])
	// 	printf("minishell: exit: too many arguments\n");
	// data->last_status = atoi(args[1]);
	// free_data_except_env(data);
	// free_env(data->env);
	// exit(atoi(args[1]));
}
