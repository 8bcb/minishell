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

typedef enum {
	ASSIGNMENT = 1,
	COMMAND = 2,
	OPTION = 3,
	PIPE = 5,
	ARGUMENT = 4,
	IN_REDIR = 6,
	OUT_REDIR = 7,
	DEL_IN_REDIR = 8,
	APP_MOD_OUT_REDIR = 9
} TokenType;

typedef struct {
	TokenType type;
	char *value;
	int line;
} Token;

typedef struct s_node{
	Token val;
	struct s_node *next;
} s_node;

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*strjoin(char const *s1, char const *s2);
void scanInput(char* input, s_node *llist);

#endif