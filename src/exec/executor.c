/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:48:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/06 13:11:20 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #### FINAL TODOLIST ####
// ADD FILES OF DIR EXEC TO MAKEFILE

//HELPERS DEBUG HELP DEBUT ############################################
static void	init_fake_cmdtable(t_data *data)
{
	//INIT une fake cmd table pour pouvoir compiler.
	data->cmd_table = malloc(sizeof(t_command));
	data->cmd_table->argv = ft_split("echo hi", ' ');
	data->cmd_table->next = NULL;
	data->cmd_table->redirs = NULL;
	data->env = NULL;
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
	printf("///CMDTABLE\\\\\\\n");
	while(cur)
	{
		i = 0;
		redirs = cur->redirs;
		while (cur->argv[i])
		{
			printf("%d, %s\n", i, cur->argv[i]);
			i++;
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

//HELPERS DEBUG HELP END ############################################

// void	prepare_all_heredocs(t_data *data)
// {
// 	return;
// }

int	exec_cmd(t_data *data, t_exec_data *ctx)
{
	t_builtin type;
	
	if(!data || !data->cmd_table || !ctx->exec_argv || !ctx)
		return (-1);
	type = is_builtin(ctx->exec_argv[0]);
	if (type != CMD)
		return (exec_builtin_parent(ctx->exec_argv, ctx->envp));
	else
		exec_external_cmd(data, ctx);
	// fork
	// child execve
	// parent waitpid
	// update last_status
	// return status
}

int	exec_single_command(t_data *data)
{
	t_exec_data	ctx;
	
	if (!data || !data->cmd_table || !data->cmd_table->argv)
		return (-1);
	init_exec_data(&ctx, data);
	if (is_only_assignment_no_cmd(data->cmd_table->argv, ctx.assign_count) == true)
		return (handle_assignment_only_command(data, &ctx));
	exec_cmd(data, &ctx);
	wrapper_free_single_command(&ctx);
	return (0);
}

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

