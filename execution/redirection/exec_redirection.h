/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:15:26 by asia              #+#    #+#             */
/*   Updated: 2026/01/18 13:13:21 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_REDIRECTION_H
# define EXEC_REDIRECTION_H

# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdio.h>
# include "../exec.h"

int		apply_redirection(t_ast *cmd);
int		save_stdio(int *saved_in, int *saved_out);
void	restore_stdio(int saved_in, int saved_out);
char	*get_last_file(char **file);
int		open_heredoc_fd(const char *delimiter);
int		open_outfile(char *outfile, int append);
int		open_infile(char *infile);
int		preprocess_heredocs(t_ast *node);

#endif