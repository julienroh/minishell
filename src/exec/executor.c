/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:48:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/21 21:02:11 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor_run(t_data *data)
{
	int	cmd_numbers;

	if (!data || !data->cmd_table || !data->cmd_table->argv)
		return ;
	cmd_numbers = count_cmd_numbers(data);
	if (prepare_all_heredocs(data) == -1)
		return ;
	signal_mute_parent();
	if (cmd_numbers == 1)
		exec_single_command(data);
	else if (cmd_numbers > 1)
		exec_multi_command(data, cmd_numbers);
	cleanup_tmpfiles_heredocs(data);
}
