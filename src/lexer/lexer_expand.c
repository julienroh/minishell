/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:43:04 by haoky             #+#    #+#             */
/*   Updated: 2026/03/03 11:38:44 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tokens(t_lexer *lexer, int number)
{
	int		i;
	int		j;
	t_part	*current;

	i = 0;
	while (i < number)
	{
		printf("TOKEN %d\n", i);
		if (lexer->tokens[i].type == WORD)
		{
			j = 0;
			current = lexer->tokens[i].parts;
			while (current != NULL)
			{
				printf("token %d part %d = %s\n", i, j, current->value);
				current = current->next;
				j++;
			}
		}
		printf("value = %s\n", lexer->tokens[i].value);
		printf("toktype = %d\n", lexer->tokens[i].type);
		i++;
	}
}

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

int	lexer_expand(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->lexer->token_total)
	{
		if (data->lexer->tokens[i].parts != NULL)
		{
			parts_expand(data, &data->lexer->tokens[i]);
			data->lexer->tokens[i].value = join_parts(data, data->lexer->tokens[i]);
		}
		//free_parts(data->lexer->tokens[i]);
		i++;
	}
	i = 0;
	print_tokens(data->lexer, data->lexer->token_total);
	return (0);
}
