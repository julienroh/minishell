/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:09:31 by adavid            #+#    #+#             */
/*   Updated: 2026/01/24 17:07:19 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*parser_env(char **env)
{
	int		i;
	t_env	*env_struct;
	t_env	*new;

	i = 0;
	env_struct = NULL;
	while (env[i])
	{
		new = env_new(env[i]);
		if (!new)
			return (NULL);
		env_add_back(&env_struct, new);
		i++;
	}
	return (env_struct);
}
