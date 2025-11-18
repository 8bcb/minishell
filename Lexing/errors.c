

#include "../minishell.h"

void _invalid_assignment_error() 
{
    printf("Invalid sign in assignment\n");
}

void _unclosed_quotes_error() 
{
    printf("Unclosed quotes\n");
}

void _invalid_redirection_error() 
{
    printf("Invalid sign after redirection operand");
}