/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:26:15 by jroh              #+#    #+#             */
/*   Updated: 2026/03/13 18:03:34 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_child(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	write(1, "\n", 1);
	close(STDIN_FILENO); // action pour niquer ça race à l'autre, mais avant je dois free all TOPLEL.
}

void	signal_exec(void)
{
	struct sigaction	sa;

	//sa.sa_handler = SIG_DFL;
	sa.sa_handler = sigint_child;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
