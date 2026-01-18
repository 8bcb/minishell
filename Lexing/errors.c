/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:46:15 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/18 12:46:54 by pkosciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_invalid_assignment_error(void)
{
	printf("Invalid assignment\n");
	return (-1);
}

int	_unclosed_quotes_error(void)
{
	printf("Unclosed quotes\n");
	return (-1);
}

int	_invalid_redirection_error(void)
{
	printf("Invalid sign after redirection operand\n");
	return (-1);
}

void	_invalid_input(void)
{
	printf("Command not found\n");
}
