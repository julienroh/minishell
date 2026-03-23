/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:43:04 by haoky             #+#    #+#             */
/*   Updated: 2026/03/23 12:12:25 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Expand the token part if needed.
*/

static void	parts_expand(t_data *data, t_token *token)
{
	int		i;
	t_part	*p;

	i = 0;
	p = token->parts;
	while (p)
	{
		if (p->expand == 1)
			expand_part(data, p, i);
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
		free_all_malloc(data);
	p = token.parts;
	while (p)
	{
		tmp = ft_strjoin(to_return, p->value);
		if (!tmp)
			free_all_malloc(data);
		free(to_return);
		to_return = tmp;
		p = p->next;
	}
	return (to_return);
}

static void	clean_empty_tokens(t_lexer *lexer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < lexer->token_total)
	{
		if (lexer->tokens[i].value[0] == '\0')
			free(lexer->tokens[i].value);
		else
		{
			lexer->tokens[j] = lexer->tokens[i];
			j++;
		}
		i++;
	}
	lexer->token_total = j;
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
			free(data->lexer->tokens[i].value);
			data->lexer->tokens[i].value = join_parts(data,
					data->lexer->tokens[i]);
		}
		i++;
	}
	clean_empty_tokens(data->lexer);
	return (0);
}
