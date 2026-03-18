/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:22:09 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/18 13:06:56 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//allocate env in char**. if error, free data, exit.
void	single_init_envp(t_data *data, char ***envp)
{
	*envp = NULL;
	*envp = env_to_envp(data->env);
	if (!*envp)
	{
		ft_putstr_fd("minishell : ", 2);
		perror("malloc");
		single_free_exit(data, 1);
	}
}
