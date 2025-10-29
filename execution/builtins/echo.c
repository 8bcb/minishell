/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 07:59:23 by asia              #+#    #+#             */
/*   Updated: 2025/10/29 10:04:25 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int builtin_echo(char **argv)
{
    int i;
    int print_newline;
    int str_len;
    
    i = 1;
    print_newline = 1;
    while (argv[i] && is_new_line(argv[i]))
    {
        print_newline = 0;
        i++;
    }
    while (argv[i])
    {
        str_len = ft_strlen(argv[i]);
        if (str_len)
            write(STDOUT_FILENO, argv[i], str_len);
        if (argv[i + 1]) write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (print_newline)
        write(STDOUT_FILENO, "\n", 1);
    return 0;
}

int is_new_line(char *str)
{
    int i;

    if (!str || str[0] != '-')
        return 0;
    if (str[1] == '\0')
        return 0;
    i = 1;
    while (str[i])
    {
        if (str[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}