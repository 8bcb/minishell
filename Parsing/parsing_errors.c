#include "../minishell.h"

int _too_many_args_error()
{
    printf("Too many arguments entered\n");
    return -1;
}

int _invalid_syntax_error()
{
    printf("Invalid syntax\n");
    return - 1;
}