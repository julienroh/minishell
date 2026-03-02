/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:38:44 by haoky             #+#    #+#             */
/*   Updated: 2026/03/02 11:42:58 by haoky            ###   ########.fr       */
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
		printf("TOKEN %d\n", i);
		if (lexer->tokens[i].type == WORD)
		{
			int	j = 0;
			current = lexer->tokens[i].parts;
			while (current != NULL)
			{
				printf("token %d part %d = %s\n", i, j, current->value);
				current = current->next;
				j++;
			}
		}
		else
			printf("operator = %s\n", lexer->tokens[i].value);
		i++;
	}
}



/*Add the char at the end of the last part of the last token*/

static void	add_char(t_data *data, t_token *token, char c)
{
	t_part	*part;
	char	*tmp;
	size_t	len;

	if (!token->parts)
		add_new_part(data, token, 1);
	part = last_part(token);
	if (!part->value)
	{
		part->value = malloc(2);
		if (!part->value)
			free_all(data);
		part->value[0] = c;
		part->value[1] = '\0';
	}
	else
	{
		len = ft_strlen(part->value);
		tmp = malloc(len + 2);
		if (!tmp)
			free_all(data);
		ft_memcpy(tmp, part->value, len);
		tmp[len] = c;
		tmp[len + 1] = '\0';
		free(part->value);
		part->value = tmp;
	}
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
	int i = 0;
	t_state state = {0, 0};
	t_token *tok;
	int	expand;
	int	new_part_needed;

	data->lexer->token_i = 0;

	while (line[i])
	{
		// skip espaces hors quotes
		if (!state.s_quote && !state.d_quote && is_space(line[i]))
		{
			i++;
			continue;
		}


		// opérateurs
		if (!state.s_quote && !state.d_quote && is_operator(line[i]))
		{
			set_operator_token(data, line, data->lexer, &i);
			continue;
		}

		// WORD : on crée une part normale **uniquement au début**
		tok = &data->lexer->tokens[data->lexer->token_i];
		tok->type = WORD;
		new_part_needed = 1;
		while (line[i] && (!is_space(line[i]) || state.s_quote || state.d_quote) && !is_operator(line[i]))
		{
			expand = 1;
			// entrée dans double quote
			if (line[i] == '"' && !state.s_quote)
			{
				change_state_dquote(&state);
				new_part_needed = 1;
				i++;
				continue;
			}

			// entrée dans simple quote
			if (line[i] == '\'' && !state.d_quote)
			{
				change_state_squote(&state);
				expand = 0;
				new_part_needed = 1;
				i++;
				continue;
			}
			t_part	*last = last_part(tok);
			if (!last || new_part_needed)
			{
				add_new_part(data, tok, expand);
				last = last_part(tok);
				new_part_needed = 0;
			}
			// ajouter caractère à la dernière part
			add_char(data, tok, line[i]);
			i++;
		}

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
