/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 12:00:09 by haoky             #+#    #+#             */
/*   Updated: 2026/03/03 13:51:17 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*build_expanded(char *str, int end, char *env)
// {
// 	char	*prefix;
// 	char	*suffix;
// 	char	*tmp;
// 	char	*result;

// 	prefix = ft_substr(str, 0, end - ft_strlen(env));
// 	suffix = ft_strdup(str + end);
// 	tmp = ft_strjoin(prefix, env);
// 	free(prefix);
// 	result = ft_strjoin(tmp, suffix);
// 	free(tmp);
// 	free(suffix);
// 	return (result);
// }

static char	*extract_id(char *str, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	if (!ft_isalnum(str[*i]) && str[*i] != '_')
		return (NULL);
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char *get_env_value(t_data *data, char *id)
{
	t_env *current = data->env;
	while (current)
	{
		if (ft_strlen(current->id) == ft_strlen(id) &&
		ft_strncmp(current->id, id, ft_strlen(id)) == 0)
			return current->value;
		current = current->next;
	}
	return NULL;
}

void expand_part(t_data *data, t_part *p)
{
    int		i;
	char	*prefix;
	char	*suffix;
	char	*id;
	char	*val;
	char	*tmp;
	char	*new_part;

	i = 0;
    while (p->value[i])
    {
		if (p->value[i] == '$' && p->expand)
        {
			prefix = ft_substr(p->value, 0, i);
			id = extract_id(p->value, &i);
			val = get_env_value(data, id);
			suffix = ft_strdup(p->value + (i + 1));
			if (!val)
				free_all(data);
			tmp = ft_strjoin(prefix, val);
			new_part = ft_strjoin(tmp, suffix);
			if (!tmp || !new_part)
				free_all(data);
			i++;
		}
    }
}
