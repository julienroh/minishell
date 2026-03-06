/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:06:56 by jroh              #+#    #+#             */
/*   Updated: 2026/02/27 15:25:34 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_new(t_env *new, char *str)
{
	print_error_identifier(str);
	free(new->id);
	free(new);
	return (0);
}

/*Create a new env if even if there is no value (no '=').
*/

t_env	*new_without_equal(t_data *data, t_env *new, char *str)
{
	new->id = ft_strdup(str);
	if (!new->id)
		free_all(data);
	new->value = NULL;
	if (check_identifier(new->id))
		return (new);
	else
		free_new(new, str);
	new->value = NULL;
	return (new);
}

/*Normal case of export (if there is a '=').
*/

static t_env	*new_with_equal(t_data *data, t_env *new, char *str, int i)
{
	if (check_identifier(ft_substr(str, 0, i)))
	{
		new->id = ft_substr(str, 0, i);
		if (!new->id)
			free_all(data);
	}
	new->value = ft_strdup(str + i + 1);
	if (!new->value)
		free_all(data);
	new->next = NULL;
	return (new);
}

t_env	*env_new(t_data *data, char *str)
{
	t_env	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		free_all(data);
	if (!ft_strchr(str, '='))
	{
		new = new_without_equal(data, new, str);
		if (!new)
			return (NULL);
		return (new);
	}
	while (str[i] && str[i] != '=')
		i++;
	new = new_with_equal(data, new, str, i);
	if (!new)
		free_all(data);
	new->printable = 1;
	return (new);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
