/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:08:03 by jroh              #+#    #+#             */
/*   Updated: 2026/03/23 11:45:10 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	already_in_struct(t_data *data, char *id, char *value)
{
	size_t	len;
	t_env	*tmp;

	tmp = data->env;
	len = ft_strlen(id);
	while (tmp)
	{
		if (ft_strncmp(tmp->id, id, len) == 0 && ft_strlen(tmp->id) == len)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			if (!tmp->value)
				free_all_malloc(data);
			tmp->printable = 1;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*Check if a string is valid to be an id.
*/

int	check_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0' || ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	while (str[i])
	{
		if (i != 0 && str[i] == '+' && str[i + 1] == '=')
			return (2);
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			if (str[i] == '=')
			break ;
			return (0);
		}
		i++;
	}
	return (1);
}

static void	add_new(t_data *data, char *id, char *value, int printable)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		free_all_malloc(data);
	new->id = id;
	new->value = value;
	if (printable == 1)
		new->printable = 1;
	else
		new->printable = 0;
	new->next = NULL;
	env_add_back(&data->env, new);
}

/*If we put in the terminal "VAR+=oui", we have to put "oui" at the end of the
value register for VAR. If VAR doesn't exist, we have to create a new env for
the id VAR that will have the value "oui".
*/

void plus_equal_condition(t_data *data, char *str, char *id, int printable)
{
	int	i;
	char	*value;
	char	*new_val;
	t_env	*var;

	i = 0;
	while (str[i] && str[i] != '+')
		i++;
	value = ft_strdup(str + i + 2);
	if (!value)
		free_all_malloc(data);
	var = find_env(data, id);
	if (!var)
	{
		add_new(data, id, value, printable);
		return ;
	}
	new_val = ft_strjoin(var->value, value);
	if (!new_val)
		free_all_malloc(data);
	free(var->value);
	var->value = new_val;
	if (printable)
		var->printable = 1;
	free(value);
}

void	equal_case(t_data *data, char *id, char *value)
{
	t_env	*var;

	var = find_env(data, id);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(value);
		if (!var->value)
			free_all_malloc(data);
		var->printable = 1;
	}
	else
		add_new(data, id, value, 1);
}
