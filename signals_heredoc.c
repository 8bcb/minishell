/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:52:32 by jziola            #+#    #+#             */
/*   Updated: 2026/01/31 12:21:27 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

extern volatile sig_atomic_t	g_sig;

static void	sigint_heredoc(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_done = 1;
}

static int	heredoc_event_hook(void)
{
	if (rl_done)
		return (1);
	return (0);
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_heredoc;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	rl_event_hook = heredoc_event_hook;
}