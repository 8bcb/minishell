

#include "../minishell.h"

int _invalid_assignment_error() 
{
    printf("Invalid assignment\n");
    return -1;
}

int _unclosed_quotes_error() 
{
    printf("Unclosed quotes\n");
    return -1;
}

int _invalid_redirection_error() 
{
    printf("Invalid sign after redirection operand\n");
    return -1;
}

void _invalid_input() {
    printf("Command not found\n");
}