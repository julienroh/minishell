/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:34:14 by adavid            #+#    #+#             */
/*   Updated: 2026/03/16 11:21:52 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig;

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		stdin_backup;

	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	stdin_backup = dup(STDIN_FILENO);
	if (argc != 1)
		return (ft_putstr_fd("Wrong number of arguments.", 2), 1);
	(void)argv;
	data.env = parser_env(&data, env);
	data.line = NULL;
	data.lexer = NULL;
	data.cmd_table = NULL;
	data.last_status = 0;
	if (!data.env)
	{
		perror("malloc");
		exit(1);
	}
	waiting_function(&data, stdin_backup);
	free_env(data.env);
	return (0);
}
