/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:52:14 by jziola            #+#    #+#             */
/*   Updated: 2026/01/24 16:35:27 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_sig;

void	setup_interactive_signals(void);
void	setup_exec_signals_parent(void);
void	setup_heredoc_signals(void);
void	disable_echoctl(void);

#endif
