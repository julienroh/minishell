/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:32:06 by haoky             #+#    #+#             */
/*   Updated: 2026/01/22 10:15:13 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	size_env(t_env *env)
{
	int	count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

int	invalid_export(char *id, char *value, char *arg)
{
	printf("bash: export: '%s': not a valid identifier\n", arg);
	free(id);
	free(value);
	return (0);
}

void	print_exit(char *line)
{
	printf("exit\n");
	free(line);
}
