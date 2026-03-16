/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfumeaux <mfumeaux@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:27:41 by jroh              #+#    #+#             */
/*   Updated: 2026/03/16 22:01:26 by mfumeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_heredoc(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	signal_mute_parent(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	signal_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

int	heredoc_cleanup(t_data *data)
{
	free_all(data);
	exit(130);
}

int	heredoc_cleanup_str(t_data *data, int fd, char *str)
{
	close(fd);
	free_all(data);
	free(str);
	if (errno == ENOMEM)
	{
		ft_putstr_fd("minishell : ", 2);
		perror("readline");
		exit(1);
	}
	ft_putstr_fd("minishell: warning: here-document", 2);
	ft_putstr_fd(" delimited by end-of-file\n", 2);
	exit(0);
}
