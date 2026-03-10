/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:09:31 by adavid            #+#    #+#             */
/*   Updated: 2026/03/10 11:43:31 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*parser_env(t_data *data, char **env)
{
	int		i;
	t_env	*env_struct;
	t_env	*new;

	i = 0;
	env_struct = malloc(sizeof(t_env));
	new = malloc(sizeof(t_env));
	if (!new || !env_struct)
		free_all(data);
	env_struct = NULL;
	new->id = ft_strdup("?");
	new->value = ft_strdup("0");
	new->printable = 0;
	new->next = NULL;
	env_add_back(&env_struct, new);
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
