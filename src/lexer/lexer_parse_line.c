/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:38:44 by haoky             #+#    #+#             */
/*   Updated: 2026/03/02 10:46:25 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tokens(t_lexer *lexer, int number)
{
	t_part	*current;
	int	i;

	i = 0;
	while (i < number)
	{
		int j = 0;
		current = lexer->tokens[i].parts;
		while (current != NULL)
		{
			printf("value = %s\n", lexer->tokens[i].value);
			printf("token %d part %d = %s\n", i, j, current->value);
			current = current->next;
			j++;
		}
		i++;
	}
}



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
	if (!new)
		free_all(data);
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
		if (!state.s_quote && !state.d_quote)
		{
			if ((i == 0 || is_space(line[i - 1]) || is_operator(line[i - 1]))
				&& !is_space(line[i]) && !is_operator(line[i]))
				count++;
			else if (is_operator(line[i]))
			{
				count++;
				if ((line[i] == '<' && line[i + 1] == '<')
					|| (line[i] == '>' && line[i + 1] == '>'))
					i++;
			}
		}
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

/*Each token contains parts which are determined by spaces, but only if we are
in normal state (not in double quote or simple quote).
*/

static void	fill_tokens(t_data *data, char *line)
{
	int		i;
	t_state	state;

	i = 0;
	state.s_quote = 0;
	state.d_quote = 0;
	data->lexer->token_i = 0;
	while (line[i])
	{
		// /* gestion des quotes */
		// if (line[i] == '"')
		// 	change_state_dquote(&state);
		// else if (line[i] == '\'')
		// 	change_state_squote(&state);
		if (!state.s_quote && !state.d_quote)
		{
			/* skip espaces */
			if (is_space(line[i]))
			{
				i++;
				continue ;
			}
			/* opérateur */
			if (is_operator(line[i]))
			{
				set_operator_token(data, line, data->lexer, &i);
				continue ;
			}
			/* WORD */
			data->lexer->tokens[data->lexer->token_i].type = WORD;
			data->lexer->tokens[data->lexer->token_i].value = NULL;
			while (line[i]
				&& (!is_space(line[i]) || state.s_quote || state.d_quote)
				&& !is_operator(line[i]))
			{
				if (line[i] == '"' && !state.s_quote)
				{
					change_state_dquote(&state);
					if (state.d_quote)
						add_new_part(data, line, i + 1);
					i++;
					continue ;
				}
				else if (line[i] == '\'' && !state.d_quote)
				{
					change_state_squote(&state);
					if (state.d_quote)
						add_new_part(data, line, i + 1);
					i++;
					continue ;
				}
				if (!last_part(&data->lexer->tokens[data->lexer->token_i]))
					add_new_part(data, line, i);
				add_char(data, line[i]);
				i++;
			}
			data->lexer->token_i++;
		}
		else
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
