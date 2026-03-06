/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_assign_utils4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 23:19:45 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/05 12:06:50 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_exec_data(t_exec_data	*exec_ctx, t_data *data)
{
	exec_ctx->fake_env = NULL;
	exec_ctx->envp = NULL;
	exec_ctx->exec_argv = NULL;
	exec_ctx->assign_count = count_prefix_assignments(data->cmd_table->argv);
	exec_ctx->exec_argv = &data->cmd_table->argv[exec_ctx->assign_count];
	return (0);
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

int	handle_assignment_only_command(t_data *data, t_exec_data *ctx)
{
	if (apply_prefix_assignments(&data->env, data->cmd_table->argv,
		ctx->assign_count) == -1)
		return (-1);
	return (0);
}

/*
Cimetiere --> gerer assign + CMD est pas dans le scope de minishell ! 
int	build_single_command_envp(t_data *data, t_exec_data *ctx)
{
	// 0 pas besoin d'un nouveau env, sinon oui.
	if (ctx->assign_count == 0)
	{
		ctx->envp = env_to_envp(data->env); //cree un env char**
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
*/