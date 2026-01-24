/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:52:32 by jziola            #+#    #+#             */
/*   Updated: 2026/01/24 14:44:36 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	g_sig = 0;

static void	sigint_interactive(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigquit_interactive(int signo)
{
	(void)signo;
	g_sig = SIGQUIT;
	rl_on_new_line();
	rl_redisplay();
}

void	setup_interactive_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sigint_interactive;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = sigquit_interactive;
	sigaction(SIGQUIT, &sa, NULL);
}
