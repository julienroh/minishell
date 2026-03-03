/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:48:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/03 16:55:42 by mfumeaux         ###   ########.fr       */
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
	data->cmd_table->argv = ft_split("VAR=42 VAR+=4 _VAR=4", ' ');
	data->cmd_table->next = NULL;
	data->cmd_table->redirs = NULL;
}
static void print_cmd_table(t_data *data)
{
	//Imprime les infos de la CMD table.
	int	i;
	t_command	*cur;
	t_redir	*redirs;
	
	cur = data->cmd_table;
	if (!data || !data->cmd_table || !data->cmd_table->argv)
	{
		printf("%s\n", "no accessible cmd table or no cmds in it");
		return;
	}
	while(cur)
	{
		i = 0;
		redirs = cur->redirs;
		while (cur->argv[i])
		{
			printf("%s\n", cur->argv[i++]);
		}
		while (redirs)
		{
			printf("%d\n", redirs->type);
			printf("%s\n", redirs->target);
			redirs = redirs->next;
		}
		cur = cur->next;
	}
}

int	count_cmd_numbers(t_data *data)
{
	//compte le nombre de cmd.s.
	int			i;
	t_command	*cur;

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
// void	prepare_all_heredocs(t_data *data)
// {
// 	return;
// }

int	handle_assignments(t_data *data)
{
	t_command *cmd;
	int	assign_count;
	int	i;

	i = 0;
	cmd = data->cmd_table;
	assign_count = count_prefix_assignments(cmd->argv);
	while(i <= assign_count - 1)
	{
		//appliquer mes one assign à tous mes assign au début.
	}
	
}

void	exec_single_command(t_data *data)
{
	t_command *cmd;
	char **exec_argv;
	
	cmd = data->cmd_table;
	if (!cmd || !cmd->argv)
		return ;
	handle_assignments(data);
	exec_argv = &cmd->argv[count_prefix_assignments(cmd->argv)];

	
}

// void	exec_pipeline(t_data *data)
// {
// 	//detect assign dans chaque pipeline
// }

void	executor_run(t_data *data)
{
	int	cmd_numbers;
	
	cmd_numbers = count_cmd_numbers(data);
	printf("debug : cmd numbers : [%d]\n", cmd_numbers); //debug
	//prepare_all_heredocs(data);
	if (cmd_numbers == 1)
		exec_single_command(data);
	// else
	// 	exec_pipeline(data);
	//free_cmdtable(&data);, autre chose a free ?

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

