/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:48:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/03 22:43:53 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #### FINAL TODOLIST ####
// ADD FILES OF DIR EXEC TO MAKEFILE

static void	init_fake_cmdtable(t_data *data) //debug
{
	//INIT une fake cmd table pour pouvoir compiler.
	data->cmd_table = malloc(sizeof(t_command));
	data->cmd_table->argv = ft_split("VAR= grep _VAR=4", ' ');
	data->cmd_table->next = NULL;
	data->cmd_table->redirs = NULL;
}
static void print_cmd_table(t_data *data) //debug
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
	printf("///CMDTABLE\\\\\\");
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
		printf("///CMDTABLEOVER\\\\\\");
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

void print_list_env(t_env *list)
{
	t_env *tmp;

	tmp = list;
	while(tmp)
	{
		printf("id = %s\n", tmp->id);
		printf("value = %s\n", tmp->value);
		printf("printable = %d\n", tmp->printable);
		tmp = tmp->next;
	}
}

//permet de brancher assigment_only (persistant)
//apply_prefix_assignments(&data->env, cmd->argv, assign_count);
// ou prefix assignments 
// fake_env = env_dup_list(data->env);
// apply_prefix_assignments(&fake_env, cmd->argv, assign_count);

int init_single_command(t_data *data, t_env **fake_env, char ***envp,
	int *assign_count)
{
	*assign_count = count_prefix_assignments(data->cmd_table->argv);
	*fake_env = NULL;
	if (assign_count > 0)
	{
		*fake_env = env_dup_list(data->env);
			if (!*fake_env)
				return (-1); // free qqch ? 
		if (apply_prefix_assignments(fake_env, data->cmd_table->argv,
			*assign_count) == -1)
			return (-1); // free qqch ? 
		*envp = env_to_envp(fake_env);
	}
	else
	{
		if (apply_prefix_assignments(&data->env, data->cmd_table->argv,
			*assign_count) == -1)
			return (-1); // free qqch ? 
	}
		*envp = env_to_envp(data->env);
	if (!envp)
		return (-1); // free qqch ? 
	return (0);
}

void	exec_single_command(t_data *data)
{
	t_command	*cmd;
	t_env		*fake_env;
	char		**envp;
	int			assign_count;
	
	cmd = data->cmd_table;
	if (!cmd || !cmd->argv)
		return ;
	if (init_single_command(data, &fake_env, &envp, &assign_count) == -1)
		return ;
	exec_cmd();
	free_double_array(envp);
	free_env_list(fake_env);
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
	free_env_list(data.env);
}

