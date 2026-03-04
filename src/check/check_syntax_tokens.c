/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 10:24:42 by jroh              #+#    #+#             */
/*   Updated: 2026/03/04 10:53:30 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(t_token *tok)
{
	if (tok->type == 2 || tok->type == 3 || tok->type == 4 || tok->type == 5)
		return (1);
	return (0);
}

int	check_syntax_tokens(t_lexer *l, int total)
{
	int	i;
	int	to_return;

	i = 0;
	to_return = 0;
	while (i < total)
	{
		if ((i == 0 || i == total - 1) && l->tokens[i].type == 1)
			to_return = 1;
		if (i > 0 && l->tokens[i].type == 1 && l->tokens[i - 1].type == 1)
			to_return = 1;
		if (i > 0 && is_redir(&l->tokens[i]) && is_redir(&l->tokens[i - 1]))
			to_return = 1;
		if (is_redir(&l->tokens[i]) && (&l->tokens[i + 1] != 0))
			to_return = 1;
		if (is_redir(&l->tokens[i + 1]) && (l->tokens[i].type != 0))
			to_return = 0;
		i++;
	}
	if (to_return == 1)
		return (printf("syntax error\n"), 1);
	return (0);
}
