/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:34:14 by adavid            #+#    #+#             */
/*   Updated: 2026/03/18 17:44:42 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig;

// static int	create_fake_env(t_data *data)
// {
// 	t_env	*new;

// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 	{
// 		ft_putstr_fd("minishell : ");
// 		perror("malloc");
// 	}
// 	new->id = ft_strdup("?");
// 	new->value = ft_strdup("0");
// 	if (!new->id || !new->value || !new)
// 		free_all_malloc(data);
// 	new->printable = 0;
// 	new->next = NULL;
// 	env_add_back(&data->env, new);
// 	while (env[i])
// 	{
// 		new = env_new(data, env[i]);
// 		if (!new)
// 			free_all_malloc(data);
// 		env_add_back(&env_struct, new);
// 		i++;
// 	}
// 	env_add_back(&env_struct, NULL);
// 	return (env_struct);
// }

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("Wrong number of arguments.", 2), 1);
	if (tcgetattr(STDIN_FILENO, &data.original_term) == -1)
		return (ft_putstr_fd("minishell :", 2), perror("tcgetattr"), 1);
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	data.env = parser_env(&data, env);
	// if (!data.env)
	// 	create_fake_env();
	data.line = NULL;
	data.lexer = NULL;
	data.cmd_table = NULL;
	data.last_status = 0;
	if (!data.env)
	{
		perror("malloc");
		exit(1);
	}
	waiting_function(&data);
	free_env(data.env);
	return (0);
}
