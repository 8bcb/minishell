/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:15:26 by asia              #+#    #+#             */
/*   Updated: 2025/11/13 10:18:17 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



int apply_redirection(const char *infile, const char *outfile, int append);
int save_stdio(int *saved_in, int *saved_out);
void restore_stdio(int saved_in, int saved_out);
char    *get_last_file(char **file);