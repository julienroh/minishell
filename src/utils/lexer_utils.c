/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:48:42 by haoky             #+#    #+#             */
/*   Updated: 2026/03/02 11:15:14 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_state_dquote(t_state *state)
{
	if (state->s_quote == 1)
		return ;
	if (state->d_quote == 0)
		state->d_quote = 1;
	else
		state->d_quote = 0;
}

void	change_state_squote(t_state *state)
{
	if (state->d_quote == 1)
		return ;
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

void	add_new_part(t_data *data, t_token *token, int expand)
{
	t_part	*new;
	t_part	*last;

	new = malloc(sizeof(t_part));
	if (!new)
		free_all(data);
	new->value = NULL;
	new->expand = expand;
	new->next = NULL;
	if (!token->parts)
		token->parts = new;
	else
	{
		last = last_part(token);
		last->next = new;
	}
}

/*Change the state depending of the actual char and the actual state.
For example if we are in the normal state and we see a quote, then we switch
in a quote state. But if we are already in a double quote state, we only switch
the state if we see another double quote (we dont switch if we see
a simple quote).
*/

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
