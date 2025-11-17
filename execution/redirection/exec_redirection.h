/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:15:26 by asia              #+#    #+#             */
/*   Updated: 2025/11/17 07:54:14 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_REDIRECTION_H
# define EXEC_REDIRECTION_H

int     apply_redirection(const char *infile, const char *outfile, int append);
int     save_stdio(int *saved_in, int *saved_out);
void    restore_stdio(int saved_in, int saved_out);
char    *get_last_file(char **file);

#endif