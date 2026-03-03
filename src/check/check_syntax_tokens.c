/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haoky <haoky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 10:24:42 by jroh              #+#    #+#             */
/*   Updated: 2026/03/03 17:35:52 by haoky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(t_toktype *tok)
{
	if (tok == T_IN || tok == T_OUT || tok == T_APPEND || tok == T_HEREDOC)
		return (1);
	return (0);
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
		if (i > 0 && lexer->tokens[i].type == 1 && lexer->tokens[i - 1].type == 1)
			to_return = 1;
		if (i > 0 && is_redir(lexer->tokens[i].type) && is_redir(lexer->tokens[i - 1].type))
			to_return = 1;
		if (is(redir(lexer->tokens[i].type)) && (lexer->tokens[i + 1].type != 0))
			to_return = 1;
	}
	if (to_return == 1)
		return (printf("syntax error\n"), 1);
}
