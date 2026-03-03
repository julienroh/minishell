/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:08:03 by jroh              #+#    #+#             */
/*   Updated: 2026/02/27 09:29:22 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	already_in_struct(t_env *env, char *id, char *value, int plus)
{
	size_t	len;
	t_env	*tmp;

	tmp = env;
	len = ft_strlen(id);
	while (tmp)
	{
		if (ft_strncmp(tmp->id, id, len) == 0
			&& ft_strlen(tmp->id) == len && plus == 0)
		{
			free(tmp->value);
			tmp->value = value;
			return (1);
		}
		else if (ft_strncmp(tmp->id, id, len) == 0
			&& ft_strlen(tmp->id) == len && plus == 1)
		{
			ft_strjoin(tmp->value, value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*Check if a string is valid to be an id.
*/

int	check_identifier(char *id)
{
	int	i;

	i = 0;
	if (!id || ft_isdigit(id[0]))
		return (0);
	while (id[i])
	{
		if (i != 0 && id[i] == '+' && id[i + 1] == '=')
			return (2);
		else if (!ft_isalnum(id[i]) && id[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*Put the value at the end of the actual string in then env struct.
*/

static void	add_end_value(t_data *data, char *id, char *value, int printable)
{
	t_env	*tmp;
	char	*old;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->id, id, ft_strlen(id))
			&& ft_strlen(tmp->id) == ft_strlen(id))
		{
			old = tmp->value;
			tmp->value = ft_strjoin(tmp->value, value);
			if (!tmp->value)
				free_all(data);
			if (printable == 1)
				tmp->printable = 1;
			free(old);
			return ;
		}
		tmp = tmp->next;
	}
}

/*If we put in the terminal "VAR+=oui", we have to put "oui" at the end of the
value register for VAR. If VAR doesn't exist, we have to create a new env for
the id VAR that will have the value "oui".
*/

void	plus_equal_condition(t_data *data, char *str, int printable)
{
	int		i;
	char	*id;
	char	*value;
	t_env	*new;

	i = 0;
	id = NULL;
	value = NULL;
	while (str[i] && str[i] != '+')
		i++;
	id = ft_substr(str, 0, i);
	value = ft_strdup(str + i + 2);
	if (!id || !value)
		free_all(data);
	new = malloc(sizeof(t_env));
	if (!new)
		free_all(data);
	if (!already_in_struct(data->env, id, value, 1))
	{
		new->id = id;
		new->value = value;
		if (printable == 1)
			new->printable = 1;
		else
			new->printable = 0;
		new->next = NULL;
		env_add_back(&data->env, new);
	}
	else
	{
		if (printable == 1)
			add_end_value(data, id, value, 1);
		else
			add_end_value(data, id, value, 0);
	}
}
