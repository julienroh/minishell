/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:08:35 by jroh              #+#    #+#             */
/*   Updated: 2026/03/23 11:48:13 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_overflow(char *arg, char *min, char *max)
{
	int		sign;
	int		len;

	sign = 1;
	if (*arg == '-' || *arg == '+')
	{
		if (*arg == '-')
			sign = -1;
		arg++;
	}
	while (*arg == '0')
		arg++;
	len = ft_strlen(arg);
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	if (sign == 1 && ft_strncmp(arg, max, 19) > 0)
		return (1);
	if (sign == -1 && ft_strncmp(arg, min, 19) > 0)
		return (1);
	return (0);
}

static int	is_valid_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static void	exit_with_code(t_data *data, long long code)
{
	free_data_except_env(data);
	free_env(data->env);
	exit(code);
}

int	exec_exit(t_data *data, char **args)
{
	long long	code;
	char		*max;
	char		*min;

	max = "9223372036854775807";
	min = "9223372036854775808";
	if (data->cmd_table->next == NULL)
		printf("exit\n");
	if (!args[1])
	exit_with_code(data, data->last_status);
	if (!is_valid_numeric(args[1]) || is_overflow(args[1], min, max) == 1)
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit_with_code(data, 2);
	}
	if (count_args(args) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	code = ft_atoll(args[1]);
	free_data_except_env(data);
	free_env(data->env);
	exit(code % 256);
}
