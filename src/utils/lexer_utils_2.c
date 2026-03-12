/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:30:33 by jroh              #+#    #+#             */
/*   Updated: 2026/03/12 10:14:32 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	test_if_new_part(t_data *data, t_token *tok, int expand, int new_part)
{
	t_part	*last;

	last = last_part(tok);
	if (!last || new_part)
	{
		add_new_part(data, tok, expand);
		last = last_part(tok);
		new_part = 0;
	}
	return (new_part);
}

int	count_operator_case(char *line, int *i, int count)
{
	if ((*i == 0 || is_space(line[*i - 1]) || is_operator(line[*i - 1]))
		&& !is_space(line[*i]) && !is_operator(line[*i]))
		count++;
	else if (is_operator(line[*i]))
	{
		count++;
		if ((line[*i] == '<' && line[*i + 1] == '<')
			|| (line[*i] == '>' && line[*i + 1] == '>'))
			(*i)++;
	}
	return (count);
}

static void	simple_operator_case(t_data *data, t_token *tok, char c, int *i)
{
	if (c == '|')
	{
		tok->type = PIPE;
		tok->value = ft_strdup("|");
		if (!tok->value)
			free_all_malloc(data);
		(*i)++;
	}
	else if (c == '<')
	{
		tok->type = T_IN;
		tok->value = ft_strdup("<");
		if (!tok->value)
			free_all_malloc(data);
		(*i)++;
	}
	else if (c == '>')
	{
		tok->type = T_OUT;
		tok->value = ft_strdup(">");
		if (!tok->value)
			free_all_malloc(data);
		(*i)++;
	}
}

void	set_operator_token(t_data *data, char *line, t_lexer *lexer, int *i)
{
	t_token	*tok;

	tok = &lexer->tokens[lexer->token_i];
	tok->parts = NULL;
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		tok->type = T_HEREDOC;
		tok->value = ft_strdup("<<");
		if (!tok->value)
			free_all_malloc(data);
		(*i) += 2;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		tok->type = T_APPEND;
		tok->value = ft_strdup(">>");
		if (!tok->value)
			free_all_malloc(data);
		(*i) += 2;
	}
	simple_operator_case(data, tok, line[*i], i);
	lexer->token_i++;
}
