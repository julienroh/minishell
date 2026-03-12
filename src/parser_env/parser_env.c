/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:09:31 by adavid            #+#    #+#             */
/*   Updated: 2026/03/12 10:14:32 by jroh             ###   ########.fr       */
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
	new = malloc(sizeof(t_env));
	new->id = ft_strdup("?");
	new->value = ft_strdup("0");
	if (!new->id || !new->value || !new)
		free_all_malloc(data);
	new->printable = 0;
	new->next = NULL;
	env_add_back(&env_struct, new);
	while (env[i])
	{
		new = env_new(data, env[i]);
		if (!new)
			free_all_malloc(data);
		env_add_back(&env_struct, new);
		i++;
	}
	env_add_back(&env_struct, NULL);
	return (env_struct);
}
