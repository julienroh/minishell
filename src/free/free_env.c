/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:58:50 by jroh              #+#    #+#             */
/*   Updated: 2026/02/26 16:53:42 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	if (!env)
		return ;
	t_env	*current;
	t_env	*next;

	current = env;
	while (current != NULL)
	{
		next = current->next;
		free(current->id);
		free(current->value);
		free(current);
		current = next;
	}
}
