/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:48:42 by haoky             #+#    #+#             */
/*   Updated: 2026/03/12 10:14:32 by jroh             ###   ########.fr       */
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
		free_all_malloc(data);
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

/*Add the char at the end of the last part of the last token*/

void	add_char(t_data *data, t_token *token, char c)
{
	t_part	*part;
	char	*tmp;
	size_t	len;

	part = last_part(token);
	if (!part->value)
	{
		part->value = malloc(2);
		if (!part->value)
			free_all_malloc(data);
		part->value[0] = c;
		part->value[1] = '\0';
	}
	else
	{
		len = ft_strlen(part->value);
		tmp = malloc(len + 2);
		if (!tmp)
			free_all_malloc(data);
		ft_memcpy(tmp, part->value, len);
		tmp[len] = c;
		tmp[len + 1] = '\0';
		free(part->value);
		part->value = tmp;
	}
}
