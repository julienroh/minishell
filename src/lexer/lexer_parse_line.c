/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:38:44 by haoky             #+#    #+#             */
/*   Updated: 2026/02/07 11:44:02 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Add the char at the end of the last part of the last token*/

static void	add_char(t_lexer *lexer, char c)
{
	t_part	*p;
	char	*new;
	char	tmp[2];

	p = last_part(&lexer->tokens[lexer->token_i]);
	if (!p)
	{
		add_new_part(lexer, "", 0);
		p = last_part(&lexer->tokens[lexer->token_i]);
	}
	tmp[0] = c;
	tmp[1] = '\0';
	new = ft_strjoin(p->value, tmp);
	free(p->value);
	p->value = new;
}

static int	number_of_tokens(char *line)
{
	int		count;
	int		i;
	t_state	state;

	count = 0;
	i = 0;
	state.s_quote = 0;
	state.d_quote = 0;
	while (line[i])
	{
		if ((i == 0 || (!is_space(line[i]) && is_space(line[i - 1])))
			&& (!state.s_quote && !state.d_quote))
			count++;
		if (line[i] == '"')
			change_state_dquote(&state);
		if (line[i] == '\'')
			change_state_squote(&state);
		i++;
	}
	return (count);
}

/*Each token contains parts which are determined by spaces, but only if we are
in normal state (not in double quote or simple quote).

*/

static void	fill_tokens(char *line, t_lexer *lexer)
{
	int		i;
	t_state	state;

	i = 0;
	state.s_quote = 0;
	state.d_quote = 0;
	while (line[i])
	{
		if ((i == 0 && !is_space(line[i]))
			|| (i > 0 && !is_space(line[i]) && is_space(line[i - 1])
				&& !state.s_quote && !state.d_quote))
		{
			lexer->token_i++;
		}
		if (state_change(&state, line[i]))
		{
			add_new_part(lexer, line, i);
		}
		else if (!is_space(line[i]) || state.s_quote || state.d_quote)
		{
			add_char(lexer, line[i]);
		}
		i++;
	}
}

/*Fonction that returns an array of struct t_lexer that contains
tokens*/

t_lexer	*lexer_parse_line(char *line)
{
	t_lexer	*lexer;
	int		number;
	int		i;

	i = 0;
	lexer = malloc(sizeof(t_lexer));
	number = number_of_tokens(line);
	lexer->token_total = number;
	lexer->token_i = -1;
	lexer->tokens = malloc(sizeof(t_token) * number);
	if (!lexer->tokens)
		return (NULL);
	while (i < number)
	{
		lexer->tokens[i].parts = NULL;
		i++;
	}
	fill_tokens(line, lexer);
	return (lexer);
}
