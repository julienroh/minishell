/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:27:41 by jroh              #+#    #+#             */
/*   Updated: 2026/03/06 09:48:24 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_heredoc(void)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

void	signal_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_heredoc();
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	
	sa.sa_handler = SIG_IGN;
	sigaction((SIGQUIT, &sa, NULL));
}
