/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 10:43:05 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/18 13:11:12 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
// TODO: remove
#include <stdio.h>
#include "libft.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

typedef enum e_node_type {
	NODE_COMMAND,
	NODE_PIPE
} t_node_type;

typedef struct s_ast {
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**argv; // ["grep", "foo", NULL]
	char			**infile; // < file
	char			**outfile; // > file, >> file
	int				append;
	int           	heredoc;     // 1 if heredoc was present
    char         	*heredoc_tmp;
	int             heredoc_fd;
} t_ast;

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

typedef enum e_token_type {
	WORD = 1,
	PIPE = 2,
	REDIR_IN = 3,
	REDIR_OUT = 4,
	REDIR_APPEND = 5,
	HEREDOC = 6,
	T_EOF = 7,
	ASSIGNMENT = 8
} t_token_type;

typedef struct s_token {
	t_token_type type;
	char *value;
} Token;

typedef struct s_node{
	Token *val;
	struct s_node *next;
} s_node;

int isWhiteSpace(char c);
int isSeparator(char c);
char* trim(char *input);

void add_node(s_node** list, Token **newToken);
void free_list(s_node **list);
void print_list(s_node *head);

//int t_command(char* input, s_node **list, int start, int *commandFlag);
int t_quoted_argument(char *input, s_node** list, int start, int quoteType);
int t_argument(char* input, s_node **list, int start);
int t_pipe(s_node **list);
int t_redirection(char *input, s_node **list, int start);

s_node* tokenizing(char* input, int* isAssignment);

void _invalid_assignment_error();
void _unclosed_quotes_error();
void _invalid_redirection_error();
void _invalid_input();

t_ast* parsing(s_node** tokens);

t_ast* create_command_node();
t_ast* create_pipe_node(t_ast* left, t_ast* right);
void print_tree(t_ast* tree, int depth);

int _too_many_args_error();
int _invalid_syntax_error();

#endif