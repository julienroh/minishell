/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:34:14 by adavid            #+#    #+#             */
/*   Updated: 2026/03/06 21:13:08 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if(argc != 1)
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
	waiting_function(&data);
	free_env(data.env);
	return (0);
}
