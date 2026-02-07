/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:06:56 by jroh              #+#    #+#             */
/*   Updated: 2026/02/07 12:25:53 by haoky            ###   ########.fr       */
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

t_env	*new_without_equal(t_env *new, char *str)
{
	new->id = ft_strdup(str);
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

t_env	*new_with_equal(t_env *new, char *str, int i)
{
	if (check_identifier(ft_substr(str, 0, i)))
		new->id = ft_substr(str, 0 , i);
	if (!new->id)
		return (free(new), NULL);
	new->value = ft_strdup(str + i + 1);
	if (!new->value)
		return (free(new->id), free(new), NULL);
	new->next = NULL;
	return (new);
}

t_env	*env_new(char *str)
{
	t_env	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	if (!ft_strchr(str, '='))
	{
		new = new_without_equal(new, str);
		if (!new)
			return (NULL);
		return (new);
	}
	while (str[i] && str[i] != '=')
		i++;
	new = new_with_equal(new, str, i);
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
