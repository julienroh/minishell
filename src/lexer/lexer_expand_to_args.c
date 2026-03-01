/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_to_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:43:04 by haoky             #+#    #+#             */
/*   Updated: 2026/03/01 12:41:15 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*The only acceptable char for the id of a value are ft_isalnum == 1 and "_".
So first, the function increase "i_dollar" until we found a forbidden char for
the id of a value. Then we take this potential id and check if there is the same
id in our env struct. If the answer is yes, we change the value after the "$" by
the value in the struct.
*/

static char	*check_expand(t_data *data, t_part *part, int *i_dollar)
{
	int		i;
	char	*check;
	t_env	*current;

	i = 0;
	(*i_dollar)++;
	current = data->env;
	check = malloc(sizeof(char) * (ft_strlen(part->value + *i_dollar) + 1));
	if (!check)
		free_all(data);
	while (part->value[*i_dollar] && (ft_isalnum(part->value[*i_dollar])
			|| part->value[*i_dollar] == '_'))
		check[i++] = part->value[(*i_dollar)++];
	check[i] = '\0';
	while (current != NULL)
	{
		if (ft_strncmp(current->id, check, ft_strlen(check)) == 0
			&& ft_strlen(check) == ft_strlen(current->id))
			return (free(check), current->value);
		current = current->next;
	}
	free(check);
	return (NULL);
}

static void	expand_part(t_data *data, t_part *part)
{
	int		i;
	char	*env_value;
	char	*old_value;

	i = 0;
	while (part->value[i])
	{
		if (part->value[i] == '$')
		{
			env_value = check_expand(data, part, &i);
			if (env_value != NULL)
			{
				old_value = part->value;
				part->value = env_value;
				free(old_value);
			}
		}
		else
			i++;
	}
}

/*Expand the token part if needed.
*/

static void	parts_expand(t_data *data, t_token *token)
{
	t_part	*p;

	p = token->parts;
	while (p)
	{
		if (p->expand == 1)
			expand_part(data, p);
		p = p->next;
	}
}

/*Make ft_strjoin on all parts of the token to have only one string.
*/

static char	*join_parts(t_data *data, t_token token)
{
	char	*to_return;
	char	*tmp;
	t_part	*p;

	to_return = ft_strdup("");
	if (!to_return)
		free_all(data);
	p = token.parts;
	while (p)
	{
		tmp = ft_strjoin(to_return, p->value);
		if (!tmp)
			free_all(data);
		free(to_return);
		to_return = tmp;
		p = p->next;
	}
	return (to_return);
}

/*Fontion that converts the struct lexer into a (char *) array. We detect if a
value needs to be expand by searching for the char "$"*/

char	**lexer_expand_to_args(t_data *data)
{
	char	**args;
	int		i;

	i = 0;
	args = malloc(sizeof(char *) * (data->lexer->token_total + 1));
	if (!args)
		free_all(data);
	while (i < data->lexer->token_total)
	{
		if (data->lexer->tokens[i].parts == NULL)
		{
			args[i] = data->lexer->tokens[i].value;
			i++;
			continue ;
		}
		parts_expand(data, &data->lexer->tokens[i]);
		args[i] = join_parts(data, data->lexer->tokens[i]);
		i++;
	}
	args[i] = NULL;
	i = 0;
	while (args[i])
		printf("args = : %s\n", args[i++]);
	return (args);
}
