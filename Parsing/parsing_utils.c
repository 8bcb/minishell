#include "../minishell.h"

t_ast* create_command_node()
{
    t_ast* node;

    node = calloc(1, sizeof(t_ast));
    if (!node)
        return NULL;
    node->type = NODE_COMMAND;
    node->argv = calloc(10, sizeof(char*));
    if (!node->argv)
    {
        free(node);
        return NULL;
    }
    node->heredoc_fd = -1;
    return node;
}

t_ast* create_pipe_node(t_ast* left, t_ast* right)
{
    t_ast* node;

    node = calloc(1, sizeof(t_ast));
    if (!node)
        return NULL;
    node->type = NODE_PIPE;
    node->left = left;
    node->right = right;
    node->heredoc_fd = -1;
    return node;
}
