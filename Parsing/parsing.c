#include "../minishell.h"

int update_argv(char* str, t_ast** node)
{
    int i;
    
    i = 0;
    while ((*node)->argv[i])
        i++;
    if (i > 8)
        return _too_many_args_error();
    (*node)->argv[i] = ft_strdup(str);
    //mistake when ft_strdup returns null
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

int assign_redirection(s_node** tokens, t_ast** node)
{
    t_token_type type;
    char* file;
    int success;
    
    type = (*tokens)->val->type;
    if ((*tokens)->next != NULL)
        file = ft_strdup((*tokens)->next->val->value);
    else
        return _invalid_syntax_error();
    success = 0;
    if (!file)
        return -1;
    if (type == REDIR_IN && (*tokens)->next->val->type == WORD) {
        success = update_redir_list(&((*node)->infile), &file);
         *tokens = (*tokens)->next;
    }
    else if ((type == REDIR_OUT || type == REDIR_APPEND) && (*tokens)->next->val->type == WORD)
    {
        success = update_redir_list(&((*node)->outfile), &file);
        if (type == REDIR_APPEND)
            (*node)->append = 1;
        *tokens = (*tokens)->next;
    }
    else 
        return _invalid_syntax_error();
    if (success == -1)
    {
        free(file);
        return _redirection_error();
    }
    //heredoc to be added
    return 1;
}

t_ast* command_parser(s_node** tokens)
{
    t_ast* newNode;
    t_token_type tok_type;
    int success;

    success = 0;
    if (*tokens == NULL)
        return NULL;
    newNode = create_command_node();
    if (newNode == NULL)
        return NULL;
    while ((*tokens) != NULL && (*tokens)->val->type != PIPE)
    {
        tok_type = (*tokens)->val->type;
        if (tok_type == WORD)
            success = update_argv((*tokens)->val->value, &newNode);
        else if (tok_type == REDIR_APPEND || tok_type == REDIR_IN || tok_type == REDIR_OUT || tok_type == HEREDOC)
            success = assign_redirection(tokens, &newNode);
        else
        {
            _invalid_syntax_error();
            free_tree(&newNode);
            return NULL;
        }
        if (success == -1)
        {
            free_tree(&newNode);
            return NULL;
        }
        (*tokens) = (*tokens)->next;
    }
    return newNode;
}

t_ast* pipeline_parser(s_node** tokens)
{
    t_ast* left;
    t_ast* right;

    left = command_parser(tokens);
    if (!left)
        return NULL;
    right = NULL;
    while ((*tokens) != NULL && (*tokens)->next != NULL 
        && (*tokens)->val->type == PIPE)
    {
        (*tokens) = (*tokens)->next;
        right = command_parser(tokens);
        if (right == NULL) {
            free_tree(&left);
            return NULL;
        }
        left = create_pipe_node(left, right);
    }
    return left;
}

t_ast* parsing(s_node** tokens)
{
    s_node** tok_list;
    t_ast* res;

    tok_list = tokens;
    res = pipeline_parser(tokens);
    free_list(tok_list);
    if (!res) 
        return NULL;
    return res;
}