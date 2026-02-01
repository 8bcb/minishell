/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 13:40:42 by asia              #+#    #+#             */
/*   Updated: 2026/02/01 13:40:43 by asia             ###   ########.fr       */
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
int		apply_all_infiles(char **infiles);
int		apply_all_outfiles(char **outfiles, int *out_append);

#endif
