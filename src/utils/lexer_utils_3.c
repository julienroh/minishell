/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 12:00:09 by haoky             #+#    #+#             */
/*   Updated: 2026/03/03 13:30:19 by haoky            ###   ########.fr       */
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

// static char	*extract_var(char *str, int *i)
// {
// 	int	start;

// 	(*i)++;
// 	start = *i;
// 	if (!ft_isalnum(str[*i]) && str[*i] != '_')
// 		return (NULL);
// 	while (ft_isalnum(str[*i]) || str[*i] == '_')
// 		(*i)++;
// 	return (ft_substr(str, start, *i - start));
//}

static char *get_env_value(t_data *data, char *var)
{
	t_env *cur = data->env;
	while (cur)
	{
		if (ft_strlen(cur->id) == ft_strlen(var) &&
		ft_strncmp(cur->id, var, ft_strlen(var)) == 0)
			return cur->value;
		cur = cur->next;
	}
	return NULL;
}

void expand_part(t_data *data, t_part *p)
{
    int i = 0;

    while (p->value[i])
    {
        if (p->value[i] == '$' && p->expand)
        {
            int start = i + 1, j = start;
            while (ft_isalnum(p->value[j]) || p->value[j] == '_')
                j++;
            char *var = ft_substr(p->value, start, j - start);
            char *env_val = get_env_value(data, var);
            free(var);

            char *env;
            if (env_val)
                env = ft_strdup(env_val);
            else
                env = ft_strdup("");

            char *prefix = ft_substr(p->value, 0, i);
            char *suffix = ft_strdup(p->value + j);
            char *tmp = ft_strjoin(prefix, env);
            char *newval = ft_strjoin(tmp, suffix);

			int	new_i = ft_strlen(prefix) + ft_strlen(env);
            free(p->value);
            p->value = newval;
            free(prefix);
            free(suffix);
            free(tmp);
            free(env);
			i = new_i;
        }
        else
            i++;
    }
}
