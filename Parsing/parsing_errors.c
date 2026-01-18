/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:54:22 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/18 15:54:23 by pkosciel         ###   ########.fr       */
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
