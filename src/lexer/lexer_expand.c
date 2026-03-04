/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:43:04 by haoky             #+#    #+#             */
/*   Updated: 2026/03/04 14:42:39 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_tokens(t_lexer *lexer, int number)
// {
// 	int		i;
// 	int		j;
// 	t_part	*current;

// 	i = 0;
// 	while (i < number)
// 	{
// 		printf("TOKEN %d\n", i);
// 		if (lexer->tokens[i].type == WORD)
// 		{
// 			j = 0;
// 			current = lexer->tokens[i].parts;
// 			while (current != NULL)
// 			{
// 				printf("token %d part %d = %s\n", i, j, current->value);
// 				current = current->next;
// 				j++;
// 			}
// 		}
// 		printf("value = %s\n", lexer->tokens[i].value);
// 		printf("toktype = %d\n", lexer->tokens[i].type);
// 		i++;
// 	}
// }

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
			//free_parts(data->lexer->tokens[i]);
		}
		i++;
	}
	//print_tokens(data->lexer, data->lexer->token_total);
	return (0);
}
