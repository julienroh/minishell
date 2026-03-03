/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_assign_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:08:52 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/03 16:30:46 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_assignment_name_len(char *word, t_assign_type type)
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

static int	set_logic(t_env *env, t_env *tmp, char *id, char *value)
{
	char *str_tmp;
	
	str_tmp = NULL;
	str_tmp = ft_strdup(value);
	if (check_malloc_ok(str_tmp))
		return (-1);
	return (free(tmp->value), tmp->value = str_tmp, 1);
}

static int	append_logic(t_env *env, t_env *tmp, char *id, char *value)
{
	char *str_tmp;
	
	str_tmp = NULL;
	str_tmp = ft_strjoin(tmp->value, value);
	if (check_malloc_ok(str_tmp))
		return (-1);
	return (free(tmp->value), tmp->value = str_tmp, 1);
	
}

int	assign_already_in_list(t_env *env, char *id, char *value,
	t_assign_type type)
{
	//renvoie -1 erreur, 1 deja dans struct, 0 a créer. //ok sans accolade dans les if ?
	size_t	len;
	t_env	*tmp;
	char	*str_tmp;

	tmp = env;
	len = ft_strlen(id);
	while (tmp)
	{
		if (ft_strncmp(tmp->id, id, len) == 0 && ft_strlen(tmp->id) == len
			&& type == SET)
			if (set_logic(env, tmp, id, value) == -1)
				return (-1);
			else
				return (1);
		else if (ft_strncmp(tmp->id, id, len) == 0 && ft_strlen(tmp->id) == len
			&& type == APPEND)
			if (append_logic(env, tmp, id, value) == -1)
				return (-1);
			else
				return (1);
		tmp = tmp->next;
	}
	return (0);
}
int	count_prefix_assignments(char **argv)
{
	//nombre de VAR=machin, VAR+=machin...
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i] && get_assignment_type(argv[i]) != NONE)
		i++;
	return (i);
}
