/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_assign_utils4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 23:19:45 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/17 13:57:23 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//compte le nombre de cmd.s.

int	count_cmd_numbers(t_data *data)
{
	int		i;
	t_com	*cur;

	i = 0;
	cur = data->cmd_table;
	if (!data || !data->cmd_table || !data->cmd_table->argv)
		return (0);
	while (cur)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

int	handle_assignment_only_command(t_data *data, int assign_count)
{
	if (apply_prefix_assignments(&data->env, data->cmd_table->argv,
			assign_count) == -1)
		return (-1);
	return (0);
}
