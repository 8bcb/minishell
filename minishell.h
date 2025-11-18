/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 10:43:05 by pkosciel          #+#    #+#             */
/*   Updated: 2025/10/11 13:01:05 by pkosciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token_type {
	COMMAND = 1,
	ARGUMENT = 2,
	PIPE = 3,
	REDIR_IN = 4,
	REDIR_OUT = 5,
	REDIR_APPEND = 6,
	HEREDOC = 7,
	T_EOF = 8,
	ASSIGNMENT = 9
} t_token_type;

typedef struct {
	t_token_type type;
	char *value;
} Token;

typedef struct s_node{
	Token val;
	struct s_node *next;
} s_node;

typedef enum e_node_type {
	NODE_COMMAND = 1,
	NODE_ARGUMENT = 2,
	NODE_PIPE = 3,
	NODE_REDIR_IN = 5,
	NODE_REDIR_OUT = 4,
	NODE_REDIR_APPEND = 6,
	NODE_HEREDOC = 7,
	NODE_EOF = 8,
} t_node_type;

typedef struct s_ast {
t_node_type type;
char **argv;
char *infile;
char *outfile;
int append;
struct s_ast *left;
struct s_ast *right;
 } t_ast;

int isWhiteSpace(char c);
int isAlphanumeric(char c);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*strjoin(char const *s1, char const *s2);
char* trim(char *input);

void add_node(s_node* list, Token *newToken);


int t_command(char* input, s_node *list, int start, int *commandFlag);
int t_argument(char* input, s_node* list, int start);
int t_pipe(s_node *list, int *commandFlag);
int t_redirection(char *input, s_node* list, int start);

int scanInput(char* input, s_node *llist);
void printList(s_node *head);

void _invalid_assignment_error();
void _unclosed_quotes_error();
void _invalid_redirection_error();

#endif