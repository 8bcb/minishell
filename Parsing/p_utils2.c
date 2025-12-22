#include "../minishell.h"

int update_argv(char* str, t_ast** node)
{
    int i;
    char* newArg;
    
    i = 0;
    while ((*node)->argv[i])
        i++;
    if (i > 8)
        return _too_many_args_error();
    newArg = ft_strdup(str);
    if (!newArg)
        return -1;
    (*node)->argv[i] = newArg;
    return 1;
}

int update_redir_list(char*** list, char** str)
{
    int i;

    i = 0;
    if (*list == NULL)
        *list = calloc(10, sizeof(char*));
    if (!*list)
        return -1;
    while ((*list)[i])
        i++;
    if (i > 8)
        return _too_many_args_error();
    (*list)[i] = *str;
    return 1;
}

int assign_redir_values(t_ast **node, char** file, t_token_type type)
{
    int rez;

    rez = 0;
    if (type == REDIR_IN)
            rez = update_redir_list(&((*node)->infile), file);
    else if (type == HEREDOC)
    {
        (*node)->heredoc = 1;
        (*node)->heredoc_tmp = *file;
    }
    else
    {
        rez = update_redir_list(&((*node)->outfile), file);
        if (type == REDIR_APPEND)
            (*node)->append = 1;
    }
    return rez;
}