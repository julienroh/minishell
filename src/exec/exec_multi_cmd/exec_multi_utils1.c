/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:38:51 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/21 19:34:37 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_v(t_data *data, t_multi *v, int n_cmd)
{
	v->i = 0;
	v->n_cmd = n_cmd;
	v->prev_fd = -1;
	v->cmd = data->cmd_table;
	v->is_last = false;
	v->pids = malloc(sizeof(pid_t) * n_cmd);
	if (!v->pids)
		return (ft_putstr_fd("minishell : ", 2),
				("malloc"), data->last_status = 1, -1);
	return (0);
}

bool	is_last_cmd(int cmdnumber, int i)
{
	if (i == (cmdnumber - 1))
		return (true);
	else
		return (false);
}
