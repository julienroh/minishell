/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:30:33 by jroh              #+#    #+#             */
/*   Updated: 2026/03/01 12:28:37 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	set_operator_token(t_data *data, char *line, t_lexer *lexer, int *i)
{
	t_token	*tok;

	tok = &lexer->tokens[lexer->token_i];
	tok->parts = NULL;
	if (line[*i] == '|')
	{
		tok->type = PIPE;
		tok->value = ft_strdup("|");
		if (!tok->value)
			free_all(data);
		(*i)++;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		tok->type = T_HEREDOC;
		tok->value = ft_strdup("<<");
		if (!tok->value)
			free_all(data);
		(*i) += 2;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		tok->type = T_APPEND;
		tok->value = ft_strdup(">>");
		if (!tok->value)
			free_all(data);
		(*i) += 2;
	}
	else if (line[*i] == '<')
	{
		tok->type = T_IN;
		tok->value = ft_strdup("<");
		if (!tok->value)
			free_all(data);
		(*i)++;
	}
	else if (line[*i] == '>')
	{
		tok->type = T_OUT;
		tok->value = ft_strdup(">");
		if (!tok->value)
			free_all(data);
		(*i)++;
	}
	lexer->token_i++;
}
