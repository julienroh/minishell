/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:10:24 by adavid            #+#    #+#             */
/*   Updated: 2026/01/22 11:23:14 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write (1, &msg[i], 1);
		i++;
	}
}

void	print_error_identifier(char *str)
{
	printf("export: '%s': not a valid identifier\n", str);
}
