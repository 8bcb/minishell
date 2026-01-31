/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:54:22 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/31 15:03:05 by pkosciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_too_many_args_error(void)
{
	printf("Too many arguments entered\n");
	return (-1);
}

int	_invalid_syntax_error(void)
{
	printf("Invalid syntax\n");
	return (-1);
}

int	_redirection_error(void)
{
	printf("Redirection error");
	return (-1);
}

t_ast	*parsing_error(t_ast **tree)
{
	_invalid_syntax_error();
	free_tree(tree);
	return (NULL);
}
