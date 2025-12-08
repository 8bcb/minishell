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
    return node;
}

void print_tree(t_ast* tree, int depth)
{
    int i = 0;

    if (tree == NULL)
        return;
    printf("Depth: %d, node type: %d\n",depth, tree->type);
    if (tree->type == NODE_COMMAND)
    {
        while (tree->argv[i])
        {
            printf("Arg %d: %s\n", i, tree->argv[i]);
            i++;
        }
    }
    print_tree(tree->left, depth + 1);
    print_tree(tree->right, depth + 1);
}