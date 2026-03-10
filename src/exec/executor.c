/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:48:08 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/10 19:47:43 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_tmpname(char **foldername, int counter)
{
	char	*num;

	if (counter == INT_MAX)
	{
		ft_putstr_fd("error : too much heredocs" , 2);
		return ;
	}
	num = ft_itoa(counter);
	if (check_malloc_ok(num) == -1)
		return ;
	*foldername = ft_strjoin("/tmp/minishell_tmp_", num);
	free(num);
	return ;
}

int	get_user_input_heredoc(t_redir *r, int fd)
{
	char *str;
	int	len;

	len = ft_strlen(r->target);
	while (1)
	{
		str = NULL;
		str = readline("> ");
		if (!str)
			return (perror("here-document delimited by end-of-file"), -1);
		if (ft_strncmp(str, r->target, len + 1) == 0)
			return (free(str), 0);
		else
		{
			ft_putstr_fd(str, fd);
			write(fd, "\n", 1);
		}
		free(str);
	}
	return (0);
}

int	handle_heredoc(t_data *data, t_redir *r, int counter)
{
	int		fd;
	char	*name;
	
	name = NULL;
	ft_tmpname(&name, counter);
	if (name == NULL)
		return (data->last_status = 1, -1);
	fd = open(name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd < 0)
		return (free(name), perror("open"), -1);
	if (get_user_input_heredoc(r, fd) == -1)
		return (close(fd), unlink(name), free(name), -1);
	close(fd);
	free(r->target);
	r->target = ft_strdup(name);
	if(!r->target)
		return (free(name), perror("malloc"), data->last_status = 1, -1);
	free(name);
	r->type = R_IN;
	return (data->last_status = 0, 0);
}

int		prepare_all_heredocs(t_data *data)
{
	t_redir		*cur_redir;
	t_command	*cur_cmd;
	int	counter;

	counter = 0;
	cur_cmd = data->cmd_table;
	while (cur_cmd)
	{
		cur_redir = cur_cmd->redirs;
		while (cur_redir)
		{
			if (cur_redir->type == R_HEREDOC)
			{
				cur_redir->was_heredoc = 1;
				if (handle_heredoc(data, cur_redir, counter) == -1)
					return (data->last_status = 1, -1);
				counter++;
			}
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
	return (0);
}

void	cleanup_heredocs(t_data *data)
{
	t_redir		*cur_redir;
	t_command	*cur_cmd;
	
	cur_cmd = data->cmd_table;
	while (cur_cmd)
	{
		cur_redir = cur_cmd->redirs;
		while (cur_redir)
		{
			if (cur_redir->was_heredoc == 1)
			{
				if (unlink(cur_redir->target) == -1)
					perror("unlink");
			}
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
	return ;
}

void	executor_run(t_data *data)
{
	int	cmd_numbers;
	
	if (!data || !data->cmd_table || !data->cmd_table->argv)
		return ; 
	cmd_numbers = count_cmd_numbers(data);
	if (prepare_all_heredocs(data) == -1)
		return ;
	if (cmd_numbers == 1)
		exec_single_command(data);
	// else
	//  	exec_multi_command(data);
	cleanup_heredocs(data);
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

