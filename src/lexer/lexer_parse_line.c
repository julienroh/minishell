/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:38:44 by haoky             #+#    #+#             */
/*   Updated: 2026/02/27 16:39:04 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Add the char at the end of the last part of the last token*/

static void	add_char(t_data *data, char c)
{
	t_part	*p;
	char	*new;
	char	tmp[2];

	p = last_part(&data->lexer->tokens[data->lexer->token_i]);
	if (!p)
	{
		add_new_part(data, "", 0);
		p = last_part(&data->lexer->tokens[data->lexer->token_i]);
	}
	tmp[0] = c;
	tmp[1] = '\0';
	new = ft_strjoin(p->value, tmp);
	free(p->value);
	p->value = new;
}

static int	number_of_tokens(t_data *data, char *line)
{
	int		count;
	int		i;
	t_state	state;
	(void)data;
	count = 0;
	i = 0;
	state.s_quote = 0;
	state.d_quote = 0;
	while (line[i])
	{
		// if ((!ft_is_delimiter(data->lexer, line, i) && (i == 0 || ft_is_delimiter(data->lexer, line, i - 1)))
		// 		&& (!state.s_quote && !state.d_quote))
		// 	count++;
		// if (line[i] == '"')
		// 	change_state_dquote(&state);
		// else if (line[i] == '\'')
		// 	change_state_squote(&state);
		// i++;
		if (((i == 0) || (ft_is_delimiter(line[i]) && (!ft_is_delimiter(line[i - 1]))) || (!is_space(line[i]) && is_space(line[i]))) && (!state.s_quote && !state.d_quote))
			count++;
		if (line[i] == '"')
			change_state_dquote(&state);
		else if (line[i] == '\'')
			change_state_squote(&state);
		i++;
	}
	if (state.s_quote != 0 || state.d_quote != 0)
		return (0);
	return (count);
}

/*Each token contains parts which are determined by spaces, but only if we are
in normal state (not in double quote or simple quote).

*/

static void	fill_tokens(t_data *data)
{
	int		i;
	t_state	state;

	i = 0;
	state.s_quote = 0;
	state.d_quote = 0;
	while (data->line[i])
	{
		if (((i == 0 && !is_space(data->line[i]))
			|| (i > 0 && ((!ft_is_delimiter(data->lexer, data->line, i)) && ft_is_delimiter(data->lexer, data->line, i-1))))
				&& (!state.s_quote && !state.d_quote))
		{
			data->lexer->token_i++;
		}
		if (state_change(&state, data->line[i]))
		{
			add_new_part(data, data->line, i);
		}
		else if (!is_space(data->line[i]) || state.s_quote || state.d_quote)
		{
			add_char(data, data->line[i]);
		}
		i++;
	}
}

/*Fonction that returns an array of struct t_lexer that contains
tokens*/

t_lexer	*lexer_parse_line(t_data *data)
{
	int		number;
	int		i;

	i = 0;
	data->lexer = malloc(sizeof(t_lexer));
	if (!data->lexer)
		free_all(data);
	number = number_of_tokens(data, data->line);
	printf("number of token = %d\n", number);
	if (number == 0)
		return (printf("invalid syntax : quote unclosed\n"), NULL);
	data->lexer->token_total = number;
	data->lexer->token_i = -1;
	data->lexer->tokens = malloc(sizeof(t_token) * number);
	if (!data->lexer->tokens)
		free_all(data);
	if (!data->lexer->tokens)
		return (NULL);
	while (i < number)
	{
		data->lexer->tokens[i].parts = NULL;
		i++;
	}
	fill_tokens(data);
	return (data->lexer);
}
