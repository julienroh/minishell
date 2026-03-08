/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:09:31 by adavid            #+#    #+#             */
/*   Updated: 2026/03/08 17:14:19 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*parser_env(t_data *data, char **env)
{
	int		i;
	t_env	*env_struct;
	t_env	*new;

	i = 0;
	env_struct = NULL;
	// new = malloc(sizeof(t_env));
	// new->id = "?";
	// new->value = "0";
	// new->next = NULL;
	// if (!new)
	// 	free_all(data);
	// env_add_back(&env_struct, new);
	while (env[i])
	{
		new = env_new(data, env[i]);
		if (!new)
			free_all(data);
		env_add_back(&env_struct, new);
		i++;
	}
	env_add_back(&env_struct, NULL);
	return (env_struct);
}
