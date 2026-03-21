/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:21:22 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/21 19:42:59 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*allocate env (list) in char ** format. if error, free data, v, exit. */

void	multi_init_envp(t_data *data, t_multi *v, char ***envp)
{
	*envp = NULL;
	*envp = env_to_envp(data->env);
	if (!*envp)
	{
		print_error("minishell : ");
		perror("malloc");
		free_exit_wrapper_child(data, v, 1);
	}
}