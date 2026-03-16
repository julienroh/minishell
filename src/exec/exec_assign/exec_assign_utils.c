/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_assign_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:08:52 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/16 15:19:15 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_assignment_name_len(char *word, t_a_ty type)
{
	int	i;

	i = 0;
	if (!word)
		return (0);
	while (word[i] != '=' && word[i])
		i++;
	if (type == APPEND)
		i--;
	return (i);
}

static int	set_logic(t_env *tmp, char *value)
{
	char	*str_tmp;

	str_tmp = NULL;
	str_tmp = ft_strdup(value);
	if (check_malloc_ok(str_tmp))
		return (-1);
	return (free(tmp->value), tmp->value = str_tmp, 1);
}

static int	append_logic(t_env *tmp, char *value)
{
	char	*str_tmp;

	str_tmp = NULL;
	str_tmp = ft_strjoin(tmp->value, value);
	if (check_malloc_ok(str_tmp))
		return (-1);
	return (free(tmp->value), tmp->value = str_tmp, 1);
}

int	assign_already_in_list(t_env *env, char *id, char *value,
	t_a_ty type)
{
	size_t	len;
	t_env	*tmp;
	bool	match;

	tmp = env;
	len = ft_strlen(id);
	while (tmp)
	{
		match = (ft_strncmp(tmp->id, id, len) == 0
				&& ft_strlen(tmp->id) == len);
		if (match && type == SET)
		{
			if (set_logic(tmp, value) == -1)
				return (-1);
			return (1);
		}
		else if (match && type == APPEND)
		{
			if (append_logic(tmp, value) == -1)
				return (-1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
	//renvoie -1 erreur, 1 deja dans struct, 0 a créer.

int	count_prefix_assignments(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i] && get_assignment_type(argv[i]) != NONE)
		i++;
	return (i);
}
