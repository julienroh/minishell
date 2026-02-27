/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:48:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/02/27 12:31:56 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #### FINAL TODOLIST ####
// ADD FILES OF DIR EXEC TO MAKEFILE


// #### THINKLIST ####
// mon ENV il arrive comment quand je dois lexec ? en liste chainee ou en argv ?

static void	init_fake_cmdtable(t_data *data)
{
	//INIT une fake cmd table pour pouvoir compiler.
	data->cmd_table = malloc(sizeof(t_command));
	data->cmd_table->argv = malloc(sizeof(char *) * 3);
	data->cmd_table->argv[0] = ft_strdup("grep");
	data->cmd_table->argv[1] = ft_strdup("hi");
	data->cmd_table->argv[2] = NULL;
	data->cmd_table->next = NULL;
	data->cmd_table->redirs = NULL;
}
static void print_cmd_table(t_data *data)
{
	//Imprime les infos de la CMD table.
	int	i;

	i = 0;
	if (!data || !data->cmd_table || !data->cmd_table->argv)
	{
		printf("%s\n", "no accessible cmd table or no cmds in it");
		return;
	}
	while(data->cmd_table)
	{
		while (data->cmd_table->argv[i])
		{
			printf("%s\n", data->cmd_table->argv[i++]);
		}
		while (data->cmd_table->redirs)
		{
			printf("%d\n", data->cmd_table->redirs->type);
			printf("%s\n", data->cmd_table->redirs->target);
			data->cmd_table->redirs = data->cmd_table->redirs->next;
		}
		data->cmd_table = data->cmd_table->next;
	}
}

int	count_cmd_numbers(t_data *data)
{
	//compte le nombre de cmd.s.
	int	i;

	i = 0;
	if (!data || !data->cmd_table || !data->cmd_table->argv) 
		return (0);
	while(data->cmd_table)
	{
		i++;
		data->cmd_table = data->cmd_table->next; 
	}
	return (i);
}
void	prepare_all_heredocs(t_data *data)
{

}

void	executor_run(t_data *data)
{
	int	cmd_numbers;
	
	cmd_numbers = count_cmd_numbers(data);
	printf("debug : cmd numbers : [%d]", cmd_numbers); //debug
	prepare_all_heredocs(data);

}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	t_data data;
	init_fake_cmdtable(&data);
	print_cmd_table(&data);
	executor_run(&data);
	free_cmdtable(&data);
}

