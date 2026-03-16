/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_assign_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 12:10:41 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/16 15:19:15 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_var_name_start(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (true);
	return (false);
}

static bool	is_valid_var_name_char(int c)
{
	if (is_valid_var_name_start(c) || (c >= '0' && c <= '9'))
		return (true);
	return (false);
}

//renvoie le type d'assign + Check les erreurs de nom de vars.

t_a_ty	get_assignment_type(char *word)
{
	int	i;

	i = 0;
	if (!word || !word[0])
		return (NONE);
	if (!is_valid_var_name_start(word[0]))
		return (NONE);
	i = 1;
	while (word[i] && is_valid_var_name_char(word[i]))
		i++;
	if (word[i] == '=')
		return (SET);
	if (word[i] == '+' && word[i + 1] == '=')
		return (APPEND);
	return (NONE);
}

static int	split_assignment_word(char *word, char **name, char **value,
	t_a_ty *type)
{
	int		len;

	*name = NULL;
	*value = NULL;
	*type = get_assignment_type(word);
	if (!word || *type == NONE)
		return (-1);
	len = get_assignment_name_len(word, *type);
	*name = ft_substr(word, 0, len);
	if (check_malloc_ok(*name))
		return (-1);
	if (*type == SET)
		len++;
	else
		len += 2;
	*value = ft_strdup(&word[len]);
	if (check_malloc_ok(*value))
		return (free(*name), *name = NULL, -1);
	return (0);
}

int	apply_one_assignment(t_env **env, char *word)
{
	int				status;
	char			*name;
	char			*value;
	t_env			*new;
	t_a_ty	type;

	status = 0;
	if (!word || !env)
		return (-1);
	status = split_assignment_word(word, &name, &value, &type);
	if (status == -1)
		return (-1);
	status = assign_already_in_list(*env, name, value, type);
	if (status == -1)
		return (free(name), name = NULL, free(value), value = NULL, -1);
	else if (status == 0)
	{
		new = lst_env_new(name, value);
		if (!new)
			return (free(name), name = NULL, free(value), value = NULL, -1);
		lst_add_back(env, new);
	}
	return (free(name), name = NULL, free(value), value = NULL, 0);
}
