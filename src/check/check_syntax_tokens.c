/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 10:24:42 by jroh              #+#    #+#             */
/*   Updated: 2026/03/04 12:04:13 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_tokens(t_lexer *lexer, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		if (lexer->tokens[i].type == PIPE)
		{
			if (i == 0 || i == total - 1)
				return (printf("syntax error\n"), 1);
			if (lexer->tokens[i + 1].type == PIPE)
				return (printf("syntax error\n"), 1);
		}
		else if (is_redir(&lexer->tokens[i]))
		{
			if (i + 1 >= total || lexer->tokens[i + 1].type != WORD)
				return (printf("syntax error\n"), 1);
		}
		i++;
	}
	return (0);
}
