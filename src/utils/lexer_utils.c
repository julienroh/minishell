/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:48:42 by haoky             #+#    #+#             */
/*   Updated: 2026/01/13 11:44:21 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_state_dquote(t_state *state)
{
	if (state->d_quote == 0)
		state->d_quote = 1;
	else
		state->d_quote = 0;
}

void	change_state_squote(t_state *state)
{
	if (state->s_quote == 1)
		state->s_quote = 0;
	else
		state->s_quote = 1;
}

t_part	*last_part(t_token *token)
{
	t_part	*to_return;

	if (!token || !token->parts)
		return (NULL);
	to_return = token->parts;
	while (to_return->next)
		to_return = to_return->next;
	return (to_return);
}

void	add_new_part(t_lexer *lexer, char *line, int i)
{
	t_part	*n;
	t_part	*p;

	n = malloc(sizeof(t_part));
	if (!n)
		return ;
	n->value = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!n->value)
	{
		free(n);
		return ;
	}
	n->value[0] = '\0';
	n->next = NULL;
	if (line[i] == '\'')
		n->expand = 0;
	else
		n->expand = 1;
	if (lexer->tokens[lexer->token_i].parts == NULL)
		lexer->tokens[lexer->token_i].parts = n;
	else
	{
		p = last_part(&lexer->tokens[lexer->token_i]);
		p->next = n;
	}
}

int	state_change(t_state *state, char c)
{
	if (c == '"' && state->d_quote == 1)
	{
		change_state_dquote(state);
		return (1);
	}
	else if (c == '\'' && state->s_quote == 1)
	{
		change_state_squote(state);
		return (1);
	}
	else if (!state->s_quote && !state->d_quote)
	{
		if (c == '"')
		{
			change_state_dquote(state);
			return (1);
		}
		if (c == '\'')
		{
			change_state_squote(state);
			return (1);
		}
	}
	return (0);
}
