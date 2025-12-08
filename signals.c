/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:00:37 by asia              #+#    #+#             */
/*   Updated: 2025/12/03 09:09:27 by asia             ###   ########.fr       */
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
    //TODO: test on linux
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigquit_interactive(int signo)
{
	(void)signo;
	g_sig = SIGQUIT;
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

void	setup_exec_signals_parent(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void sigint_heredoc(int signo)
{
    (void)signo;
    g_sig = SIGINT;
    write(1, "\n", 1);
}

void    setup_heredoc_signals(void)
{
    struct sigaction    sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigint_heredoc;
    sigaction(SIGINT, &sa, NULL);
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
}