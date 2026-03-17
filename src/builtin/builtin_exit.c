/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:08:35 by jroh              #+#    #+#             */
/*   Updated: 2026/03/17 16:03:08 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_valid_numeric(char *arg)
{
    int    i;

    i = 0;
    while (arg[i])
    {
        if (ft_isdigit(arg[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

static int    count_args(char **args)
{
    int    i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

int    exec_exit(t_data *data, char **args)
{
    printf("exit\n");
    if (!args[1])
    {
        free_data_except_env(data);
        free_env(data->env);
        exit(data->last_status);
    }
    if (!is_valid_numeric(args[1]))
    {
        printf("minishell: exit: %s: numeric argument required\n", args[1]);
        free_data_except_env(data);
        free_env(data->env);
        exit (2);
    }
    if (count_args(args) > 2)
    {
        printf("minishell: exit: too many arguments\n");
        return (1);
    }
    free_data_except_env(data);
    free_env(data->env);
    if (ft_atoll(args[1]) > 255)
        exit(255);
    exit(ft_atoi(args[1]));
}