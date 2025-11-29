#include "../minishell.h"

t_ast* create_ast(t_node_type type) {
    t_ast* newAst;

    newAst = malloc(sizeof(t_ast));
    newAst->type = type;
    return newAst;
}

int assign_to_node(t_ast* ast_node, s_node* tokens_node)
{
    t_token_type tokenType = tokens_node->val->type;
    if (tokenType == REDIR_IN || tokenType == REDIR_OUT || tokenType == REDIR_APPEND)
    {
        if (tokens_node->next->val->value) {
            if (tokenType == REDIR_IN)
                ast_node->infile = &tokens_node->next->val->value;
            else
                ast_node->outfile = &tokens_node->next->val->value;
            if (tokenType == REDIR_APPEND)
                ast_node->append = 1;
        }
        else
            return -1;
    }
    else if (tokens_node->val->type == HEREDOC)
        ast_node->heredoc = 1;
    //if heredoc arguments after that should be added to heredoc_tmp
    //else add to argv list;
    return 0;
}

int read_list(s_node* list, t_ast* tree) 
{
    s_node* currNode;
    Token* currToken;
    t_ast* prevRoot;
    t_ast* lastAdded;

    currNode = list;
    while (currNode != NULL)
    {
        currToken = currNode->val;
        if (currToken->type == COMMAND && tree == NULL)
        {
            tree = create_ast(NODE_COMMAND);
            prevRoot = tree;
            lastAdded = tree;
        }
        else if (currToken->type == COMMAND && tree != NULL) 
        {
            lastAdded = create_ast(NODE_COMMAND);
            if (tree->type == NODE_PIPE)
                tree->right = lastAdded;
            //else clear tree and token list and exit with error
        }
        else if (currToken->type == PIPE)
        {
            tree = create_ast(NODE_PIPE);
            tree->left = prevRoot;
            prevRoot = tree;
            lastAdded = tree;
        }
        else if (currToken->type == REDIR_APPEND || currToken->type == REDIR_IN || currToken->type == REDIR_OUT) {
            if (assign_to_node(lastAdded,currNode) == -1)
                return -1;
            else
                currNode = currNode->next;
        }
        else
            assign_to_node(lastAdded, currNode);
        currNode = currNode->next;
    }
    return 0;
}