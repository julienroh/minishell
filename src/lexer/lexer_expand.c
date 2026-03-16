/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:43:04 by haoky             #+#    #+#             */
/*   Updated: 2026/03/16 11:16:16 by jroh             ###   ########.fr       */
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
			data->lexer->tokens[i].value = join_parts(data,
					data->lexer->tokens[i]);
		}
		i++;
	}
	return (0);
}
