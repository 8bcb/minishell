

#include "../minishell.h"

void _invalid_assignment_error() 
{
    printf("Invalid sign in assignment\n");
}

int _unclosed_quotes_error() 
{
    printf("Unclosed quotes\n");
    return -1;
}

void _invalid_redirection_error() 
{
    printf("Invalid sign after redirection operand\n");
}

void _invalid_input() {
    printf("Provided input is incorrect\n");
}