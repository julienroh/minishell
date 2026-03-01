/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_assign_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:08:52 by mfumeaux          #+#    #+#             */
/*   Updated: 2026/03/01 22:26:16 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_assignment_name_len(char *word, t_assign_type type)
{
	int i;

	i = 0;
	if (!word)
		return (0);
	while (word[i] != '=')
		i++;
	if (type == APPEND)
		i--;
	return (i);
}

int	split_assignment_word(char *word, char **name, char **value, t_assign_type *type)
{
	char	*tmp;
	int		len;
	int		i;

	*name = NULL;
	*value = NULL;
	*type = get_assignment_type(word);
	i = 0;
	if (!word || *type == NONE)
		return (1);
	len = get_assignment_name_len(word, *type);
	*name = ft_substr(word, 0, len);
	if (*type == SET)
		len++;
	else
		len += 2;
	*value = ft_strdup(&word[len]);
	if (!*value)
		return(free(*name), *name = NULL, 1);
	return (0);
}

int	apply_one_assignment(t_env **env, char *word)
{
	char			*name;
	char			*value;
	t_assign_type	type;
	t_env			*new;

	if (!word || !env)
		return (1);
	if (split_assignment_word(word, &name, &value, &type) != 0)
		return (1);
	//coder logique si append, logique si add.
	if (type == APPEND)
	{
		if (!already_in_struct(env, name, value, 0))
		{
			new = env_new(arg);
			new->printable = 0;
			env_add_back(&env, new);
		}
	}

}
