/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:52:58 by haoky             #+#    #+#             */
/*   Updated: 2026/03/17 15:45:44 by jroh             ###   ########.fr       */
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
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	if (!ft_isalnum(str[*i]) && str[*i] != '_')
		return (NULL);
	while (ft_isalnum(str[*i]) || str[*i] == '_')
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

static void	initialize_expand(t_expand *expand, t_part *p, int i)
{
	expand->suffix = ft_strdup(p->value + i);
	expand->tmp = ft_strjoin(expand->prefix, expand->val);
	expand->new_part = ft_strjoin(expand->tmp, expand->suffix);
}

void	expand_part(t_data *data, t_part *p, int i)
{
	t_expand	expand;

	while (p->value[i])
	{
		if (p->value[i] == '$' && p->expand && p->value[i + 1] != '\0')
		{
			expand.prefix = ft_substr(p->value, 0, i);
			expand.id = extract_id(p->value, &i);
			if (expand.id && expand.id[0] == '?')
				expand.val = ft_itoa(data->last_status);
			else
				expand.val = get_env_value(data, expand.id);
			if (!expand.val)
				expand.val = "";
			initialize_expand(&expand, p, i);
			if (!expand.tmp || !expand.suffix || !expand.id || !expand.prefix)
				free_all_malloc(data);
			free(p->value);
			p->value = expand.new_part;
			i = ft_strlen(expand.tmp);
			free_expand(&expand);
		}
		else
			i++;
	}
}
