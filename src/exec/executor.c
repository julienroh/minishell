/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:48:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/20 14:07:08 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	last_arg_update_env(t_env *env, t_data *data)
{
	t_env	*cur;
	int		i;
	
	i = 0;
	cur = env;
	while (data->cmd_table->argv[i] != 0)
		i++;
	i--;
	while (cur)
	{
		if (ft_strncmp(cur->id , "_", 1) == 0)
		{
			free(cur->value);
			cur->value = NULL;
			cur->value = ft_strdup(data->cmd_table->argv[i]);
			if (!cur->value)
			{
				ft_putstr_fd("minishell : ", 2);
				perror("malloc");
			}
			return ;
		}
		cur = cur->next;
	}
	return ;
}

void	executor_run(t_data *data)
{
	int	cmd_numbers;

	if (!data || !data->cmd_table || !data->cmd_table->argv)
		return ;
	last_arg_update_env(data->env, data);
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
