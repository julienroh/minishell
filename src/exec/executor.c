/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:48:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/04 18:38:53 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #### FINAL TODOLIST ####
// ADD FILES OF DIR EXEC TO MAKEFILE

//HELPERS DEBUG HELP DEBUT
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

//HELPERS DEBUG HELP DEBUT

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

//si seulement ARG=42 par exemple.
int	handle_assignment_only_command(t_data *data, t_exec_data *ctx)
{
	if (apply_prefix_assignments(&data->env, data->cmd_table->argv,
		ctx->assign_count) == -1)
		return (-1);
	return (0);
}

int	build_single_command_envp(t_data *data, t_exec_data *ctx)
{
	// 0 pas besoin d'un nouveau env, sinon oui.
	if (ctx->assign_count == 0)
	{
		ctx->envp = env_to_envp(data->env);
		if (!ctx->envp)
			return (-1);
	}
	else
	{
		ctx->fake_env = env_dup_list(data->env);
		if (!ctx->fake_env)
			return (-1);
		if (apply_prefix_assignments(&ctx->fake_env, data->cmd_table->argv,
			ctx->assign_count) == -1)
			return (free_env_list(ctx->fake_env), ctx->fake_env = NULL, -1);
		ctx->envp = env_to_envp(ctx->fake_env);
		if (!ctx->envp)
			return (free_env_list(ctx->fake_env), ctx->fake_env = NULL, -1);
	}
	return (0);
}

int	init_exec_data(t_exec_data	*exec_ctx, t_data *data)
{
	exec_ctx->fake_env = NULL;
	exec_ctx->envp = NULL;
	exec_ctx->exec_argv = NULL;
	exec_ctx->assign_count = count_prefix_assignments(data->cmd_table->argv);
	exec_ctx->exec_argv = &data->cmd_table->argv[exec_ctx->assign_count];
	return (0);
}

int	exec_single_command(t_data *data)
{
	t_exec_data	ctx;
	
	if (!data || !data->cmd_table || !data->cmd_table->argv)
		return (-1);
	init_exec_data(&ctx, data);
	if (is_only_assignment_no_cmd(data->cmd_table->argv, ctx.assign_count) == true)
		return (handle_assignment_only_command(data, &ctx));
	if (build_single_command_envp(data, &ctx) == -1)
		return (exec_free_single_command(&ctx), -1);
	//quand j'arrive ici, j'ai mes arg= arg+= gérer, un envp prêt pour les commandes.
	//si seulement $var ? créer un builtin expand ? pas deja fait ?
	//exec_cmd();
	exec_free_single_command(&ctx);
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

