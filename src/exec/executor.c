/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:48:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/10 11:44:54 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		prepare_all_heredocs(t_data *data)
{
	t_redir		*cur_redir;
	t_command	*cur_cmd;
	char		foldername;

	foldername = ft_bullshitname();
	cur_redir = data->cmd_table;
	while (cur_cmd)
	{
		cur_redir = cur_cmd->redirs;
		while (cur_redir)
		{
			
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
	return (0);
}

void	executor_run(t_data *data)
{
	int	cmd_numbers;
	
	if (!data || !data->cmd_table || !data->cmd_table->argv)
		return ; 
	cmd_numbers = count_cmd_numbers(data);
	//check_redirs - si faux ->prepare heredoc jusqu'au redir de merd.
	//prepare_all_heredocs(data);
	if (cmd_numbers == 1)
		exec_single_command(data);
	// else
	//  	exec_multi_command(data);
	//cleanup_heredocs
	//Check ici : je dois free des trucs ? 
}

//DEBUG PRINT :



// void print_list_env(t_env *list)
// {
// 	t_env *tmp;

// 	tmp = list;
// 	while(tmp)
// 	{
// 		printf("id = %s\n", tmp->id);
// 		printf("value = %s\n", tmp->value);
// 		printf("printable = %d\n", tmp->printable);
// 		tmp = tmp->next;
// 	}
// }



// static void print_cmd_table(t_data *data)
// {
// 	//Imprime les infos de la CMD table.
// 	int	i;
// 	t_command	*cur;
// 	t_redir	*redirs;
	
// 	cur = data->cmd_table;
// 	if (!data || !data->cmd_table || !data->cmd_table->argv)
// 	{
// 		printf("%s\n", "no accessible cmd table or no cmds in it");
// 		return;
// 	}
// 	printf("///CMDTABLE\\\\\\\n");
// 	while(cur)
// 	{
// 		i = 0;
// 		redirs = cur->redirs;
// 		while (cur->argv[i])
// 		{
// 			printf("%d, %s\n", i, cur->argv[i]);
// 			i++;
// 		}
// 		while (redirs)
// 		{
// 			printf("%d\n", redirs->type);
// 			printf("%s\n", redirs->target);
// 			redirs = redirs->next;
// 		}
// 		cur = cur->next;
// 	}
// 		printf("///CMDTABLEOVER\\\\\\");
// }

