#include "../minishell.h"

int update_argv(s_node** tokens, t_ast** node)
{
    int i = 0;
    while ((*node)->argv[i])
        i++;
    if (i > 9)
        return _too_many_args_error();
    (*node)->argv[i] = ft_strdup((*tokens)->val->value);
    return 1;
}

t_ast* command_parser(s_node** tokens)
{
    t_ast* newNode;
    t_token_type tok_type;

    if (*tokens == NULL)
        return NULL;
    newNode = create_command_node();
    if (newNode == NULL)
        return NULL;
    while ((*tokens) != NULL && (*tokens)->val->type != PIPE)
    {
        tok_type = (*tokens)->val->type;
        if (tok_type == WORD)
            update_argv(tokens, &newNode);
        //else if (tok_type == REDIR_APPEND || tok_type == REDIR_IN || tok_type == REDIR_OUT || tok_type == HEREDOC)
            //assign_redirection();
        else
        {
            _invalid_syntax_error();
            //free ast
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