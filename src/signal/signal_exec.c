/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:26:15 by jroh              #+#    #+#             */
/*   Updated: 2026/03/16 10:36:49 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_child(int sig) // superflu i guess.
{
	(void)sig;
	g_sig = SIGINT;
	write(1, "\n", 1);
}

void	signal_exec(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	// sa.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa, NULL);
}
