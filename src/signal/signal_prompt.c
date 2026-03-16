/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:25:41 by jroh              #+#    #+#             */
/*   Updated: 2026/03/16 23:47:35 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_prompt(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	write(1, "^C\n", 3);        // 1. Fait un vrai retour à la ligne visuel
	rl_on_new_line();           // 2. Dit à readline qu'on a bougé le curseur sur une nouvelle ligne
	rl_replace_line("", 0);     // 3. Efface le contenu du buffer interne de readline (vide la ligne)
	rl_redisplay();				// 4. Merci gemini omfg.
}

void	signal_prompt(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_prompt;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
