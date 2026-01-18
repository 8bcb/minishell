/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:45:09 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/18 16:48:35 by pkosciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirection_parser(t_node **tokens, t_ast **node)
{
	t_token_type	type;
	char			*file;
	int				success;

	type = (*tokens)->val->type;
	if ((*tokens)->next && (*tokens)->next->val->type == WORD)
	{
		file = ft_strdup((*tokens)->next->val->value);
		if (!file)
			return (-1);
		success = assign_redir_values(node, &file, type);
		if (success == -1)
		{
			free(file);
			return (_redirection_error());
		}
		*tokens = (*tokens)->next;
	}
	else
		return (_invalid_syntax_error());
	return (1);
}

int	assign_if_valid_values(t_node **tokens, t_ast **node,
	t_token_type tok_type)
{
	int	rez;

	rez = 0;
	if (tok_type == WORD)
		rez = update_argv((*tokens)->val->value, node);
	else if (tok_type == REDIR_APPEND || tok_type == REDIR_IN
		|| tok_type == REDIR_OUT || tok_type == HEREDOC)
		rez = redirection_parser(tokens, node);
	else
		return (-1);
	return (rez);
}

t_ast	*command_parser(t_node **tokens)
{
	t_ast			*new_node;
	t_token_type	tok_type;
	int				success;

	success = 0;
	if (*tokens == NULL)
		return (NULL);
	new_node = create_command_node();
	if (new_node == NULL)
		return (NULL);
	while ((*tokens) != NULL && (*tokens)->val->type != PIPE)
	{
		tok_type = (*tokens)->val->type;
		success = assign_if_valid_values(tokens, &new_node, tok_type);
		if (success == -1)
		{
			free_tree(&new_node);
			return (NULL);
		}
		(*tokens) = (*tokens)->next;
	}
	return (new_node);
}

t_ast	*pipeline_parser(t_node **tokens)
{
	t_ast	*left;
	t_ast	*right;

	left = command_parser(tokens);
	if (!left)
		return (NULL);
	right = NULL;
	while ((*tokens) != NULL && (*tokens)->next != NULL
		&& (*tokens)->val->type == PIPE)
	{
		(*tokens) = (*tokens)->next;
		right = command_parser(tokens);
		if (right == NULL)
		{
			_invalid_syntax_error();
			free_tree(&left);
			return (NULL);
		}
		left = create_pipe_node(left, right);
	}
	return (left);
}

t_ast	*parsing(t_node **tokens)
{
	t_node	**tok_list;
	t_ast	*res;

	tok_list = tokens;
	res = pipeline_parser(tokens);
	free_list(tok_list);
	if (!res)
		return (NULL);
	return (res);
}
