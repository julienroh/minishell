/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:38:44 by haoky             #+#    #+#             */
/*   Updated: 2026/03/02 18:42:18 by haoky            ###   ########.fr       */
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
// 		printf("operator = %s\n", lexer->tokens[i].value);
// 		printf("toktype = %d\n", lexer->tokens[i].type);
// 		i++;
// 	}
// }

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
		if (!state.s_quote && !state.d_quote)
			count = count_operator_case(line, &i, count);
		if (line[i] == '"')
			change_state_dquote(&state);
		else if (line[i] == '\'')
			change_state_squote(&state);
		i++;
	}
	if (state.s_quote || state.d_quote)
		return (0);
	return (count);
}

static int	handle_quotes(t_state *state, char c, int *i)
{
	if (c == '"' && !state->s_quote)
	{
		change_state_dquote(state);
		(*i)++;
		return (1);
	}
	if (c == '\'' && !state->d_quote)
	{
		change_state_squote(state);
		(*i)++;
		return (0);
	}
	return (0);
}

static int	handle_word(t_data *data, t_state state, char *line, int i)
{
	int		new_part_needed;
	int		expand;
	t_token	*tok;

	new_part_needed = 1;
	tok = &data->lexer->tokens[data->lexer->token_i];
	tok->type = WORD;
	tok->value = NULL;
	while (line[i] && (!is_space(line[i]) || state.s_quote || state.d_quote)
		&& (!is_operator(line[i]) || state.d_quote || state.s_quote))
	{
		expand = 1;
		if ((line[i] == '"' && !state.s_quote)
			|| (line[i] == '\'' && !state.d_quote))
		{
			expand = handle_quotes(&state, line[i], &i);
			new_part_needed = 1;
			continue ;
		}
		new_part_needed = test_if_new_part(data, tok, expand, new_part_needed);
		add_char(data, tok, line[i]);
		i++;
	}
	return (i);
}

/*Each token contains parts which are determined by spaces or operators,
but only if we are in normal state (not in double quote or simple quote).
*/

static void	fill_tokens(t_data *data, char *line)
{
	int		i;
	t_state	state;

	i = 0;
	state.d_quote = 0;
	state.s_quote = 0;
	data->lexer->token_i = 0;
	while (line[i])
	{
		if (!state.s_quote && !state.d_quote && is_space(line[i]))
		{
			i++;
			continue ;
		}
		if (!state.s_quote && !state.d_quote && is_operator(line[i]))
		{
			set_operator_token(data, line, data->lexer, &i);
			continue ;
		}
		i = handle_word(data, state, line, i);
		data->lexer->token_i++;
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
	number = number_of_tokens(data->line);
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
	fill_tokens(data, data->line);
	print_tokens(data->lexer, number);
	return (data->lexer);
}
