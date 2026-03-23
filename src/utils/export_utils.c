/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:08:03 by jroh              #+#    #+#             */
/*   Updated: 2026/03/20 17:30:34 by haoky            ###   ########.fr       */
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
	if (!str || str[0] == '\0' || ft_isdigit(str[0]))
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

/*Put the value at the end of the actual string in then env struct.
*/

// static void	add_end_value(t_data *data, char *id, char *value, int printable)
// {
// 	t_env	*tmp;
// 	char	*old;

// 	tmp = data->env;
// 	while (tmp)
// 	{
// 		if (!ft_strncmp(tmp->id, id, ft_strlen(id))
// 			&& ft_strlen(tmp->id) == ft_strlen(id))
// 		{
// 			old = ft_strdup(tmp->value);
// 			tmp->value = ft_strjoin(tmp->value, value);
// 			if (!tmp->value)
// 				free_all_malloc(data);
// 			if (printable == 1)
// 				tmp->printable = 1;
// 			free(old);
// 			return ;
// 		}
// 		tmp = tmp->next;
// 	}
// }

// static void	add_new(t_data *data, t_env *new, char *id, int printable)
// {
// 	new->id = id;
// 	if (printable == 1)
// 		new->printable = 1;
// 	else
// 		new->printable = 0;
// 	new->next = NULL;
// 	env_add_back(&data->env, new);
// }

/*If we put in the terminal "VAR+=oui", we have to put "oui" at the end of the
value register for VAR. If VAR doesn't exist, we have to create a new env for
the id VAR that will have the value "oui".
*/

void plus_equal_condition(t_data *data, char *str, char *id, int printable)
{
	int	i;
	char	*value;
	t_env	*tmp;

	i = 0;
	printf("je suis ici\n");
	while (str[i] && str[i] != '+')
		i++;
	value = ft_strdup(str + i + 2);
	if (!value)
		free_all_malloc(data);
	tmp = data->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->id, id, ft_strlen(id))
			&& ft_strlen(tmp->id) == ft_strlen(id))
		{
			char *new_val = ft_strjoin(tmp->value, value);
			if (!new_val)
				free_all_malloc(data);
			free(tmp->value);
			tmp->value = new_val;
			if (printable)
				tmp->printable = 1;
			free(value);
			return ;
		}
		tmp = tmp->next;
	}
}
