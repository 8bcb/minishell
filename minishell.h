/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 10:43:05 by pkosciel          #+#    #+#             */
/*   Updated: 2025/10/29 09:46:52 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
// TODO: remove
#include <stdio.h>
#include "libft.h"

typedef enum e_node_type {
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_HEREDOC
} t_node_type;

typedef struct s_ast {
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**argv; // ["grep", "foo", NULL]
	char			**infile; // < file
	char			**outfile; // > file, >> file
	int				append;
} t_ast;

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

void scanInput(char* input);

#endif