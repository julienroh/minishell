/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:12:44 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/05 12:06:47 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Duplique un seul node (id, value, printable).
Retourne NULL si erreur malloc.
*/
static t_env	*dup_env_node(t_env *src)
{
	t_env	*new_node;

	if (!src)
		return (NULL);
	new_node = lst_env_new(src->id, src->value);
	if (!new_node)
		return (NULL);
	new_node->printable = src->printable;
	return (new_node);
}

/*
Duplique toute la liste d'environnement.
Retourne NULL si erreur malloc (et libère ce qui a déjà été créé).
*/
t_env	*env_dup_list(t_env *src)
{
	t_env	*new_list;
	t_env	*new_node;

	new_list = NULL;
	while (src)
	{
		new_node = dup_env_node(src);
		if (!new_node)
			return (free_env_list(new_list), NULL);
		lst_add_back(&new_list, new_node);
		src = src->next;
	}
	return (new_list);
}