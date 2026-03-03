/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 10:24:42 by jroh              #+#    #+#             */
/*   Updated: 2026/03/03 14:42:48 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(t_toktype *tok)
{
	
}

int	check_syntax_tokens(t_lexer *lexer, int total)
{
	int	i;
	int	to_return;

	i = 0;
	to_return = 0;
	while (i < total)
	{
		if ((i == 0 || i == total - 1) && lexer->tokens[i].type == 1)
			to_return = 1;
		if (lexer->tokens[i].type == 1 && lexer->tokens[i - 1].type == 1)
			to_return = 1;

	}
	if (to_return == 1)
		return (printf("syntax error\n"), 1);
}