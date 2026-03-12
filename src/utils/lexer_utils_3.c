/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 12:00:09 by haoky             #+#    #+#             */
/*   Updated: 2026/03/11 13:55:52 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_expand(t_expand *expand)
{
	free(expand->prefix);
	free(expand->suffix);
	free(expand->tmp);
	if (expand->id)
		free(expand->id);
}

static char	*extract_id(char *str, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	if (!ft_isalnum(str[*i]) && str[*i] != '_' && str[*i] != '?')
		return (NULL);
	while (ft_isalnum(str[*i]) || str[*i] == '_' || str[*i] == '?')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*get_env_value(t_data *data, char *id)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (ft_strncmp(current->id, id, ft_strlen(id) + 1) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	expand_part(t_data *data, t_part *p, int i)
{
	t_expand	expand;

	while (p->value[i])
	{
		if (p->value[i] == '$' && p->expand)
		{
			expand.prefix = ft_substr(p->value, 0, i);
			expand.id = extract_id(p->value, &i);
			expand.val = get_env_value(data, expand.id);
			if (!expand.val)
				expand.val = "";
			expand.suffix = ft_strdup(p->value + i);
			expand.tmp = ft_strjoin(expand.prefix, expand.val);
			expand.new_part = ft_strjoin(expand.tmp, expand.suffix);
			if (!expand.tmp || !expand.suffix || !expand.id || !expand.prefix)
				free_all(data);
			free(p->value);
			p->value = expand.new_part;
			i = ft_strlen(expand.tmp);
			free_expand(&expand);
		}
		else
			i++;
	}
}
