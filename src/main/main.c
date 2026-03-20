/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:34:14 by adavid            #+#    #+#             */
/*   Updated: 2026/03/20 14:27:35 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig;

static void main_error(void)
{
		ft_putstr_fd("minishell : ", 2);
		perror("malloc");
		exit(1);
}

static int	create_fake_env(t_data *data, char **argv)
{
	if (create_pwd(data) == -1)
		return (1);
	if (create_shlvl(data) == -1)
		return (1);
	if (create_path(data, argv) == -1)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc != 1)
		return (ft_putstr_fd("Wrong number of arguments.", 2), 1);
	if (tcgetattr(STDIN_FILENO, &data.original_term) == -1)
		return (ft_putstr_fd("minishell :", 2), perror("tcgetattr"), 1);
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	data.env = parser_env(&data, env);
	incr_shlvl(data.env);
	if (!env || !*env)
		 if (create_fake_env(&data, argv) == -1)
			return (1);
	data.line = NULL;
	data.lexer = NULL;
	data.cmd_table = NULL;
	data.last_status = 0;
	if (!data.env)
		main_error();
	waiting_function(&data);
	free_env(data.env);
	return (0);
}
