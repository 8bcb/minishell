/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:35:19 by pkosciel          #+#    #+#             */
/*   Updated: 2026/02/01 13:28:52 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*create_command_node(void)
{
	t_ast	*node;

	node = calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_COMMAND;
	node->argv = calloc(10, sizeof(char *));
	if (!node->argv)
	{
		free(node);
		return (NULL);
	}
	node->heredoc_fd = -1;
	return (node);
}

t_ast	*create_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->left = left;
	node->right = right;
	node->heredoc_fd = -1;
	return (node);
}

void	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_tree(t_ast **tree)
{
	t_ast	*node;

	if (!tree || !*tree)
		return ;
	node = *tree;
	free_tree(&node->left);
	free_tree(&node->right);
	free_str_arr((*tree)->argv);
	free_str_arr((*tree)->infile);
	free_str_arr((*tree)->outfile);
	free((*tree)->out_append);
	if (node->heredoc_tmp)
		free(node->heredoc_tmp);
	free(node);
	*tree = NULL;
}

// void	print_tree(t_ast	*tree, int depth)
// {
// 	int	i = 0;
// 	int	j = 0;
// 	int	k = 0;

// 	if (tree == NULL)
// 		return ;
// 	printf("Depth: %d, node type: %d\n", depth, tree->type);
// 	if (tree->type == NODE_COMMAND)
// 	{
// 		while (tree->argv[i])
// 		{
// 			printf("Arg %d: %s\n", i, tree->argv[i]);
// 			i++;
// 		}
// 		if (tree->heredoc)
// 			printf("Heredoc flag: %d\n", tree->heredoc);
// 		if (tree->heredoc_tmp)
// 			printf("Heredoc delimiter: %s\n", tree->heredoc_tmp);
// 		printf("Append flag: %d\n", tree->append);
// 		while (tree->infile && tree->infile[j])
// 		{
// 			printf("Infile %d: %s\n", j, tree->infile[j]);
// 			j++;
// 		}
// 		while (tree->outfile && tree->outfile[k])
// 		{
// 			printf("Outfile %d: %s\n", k, tree->outfile[k]);
// 			k++;
// 		}
// 	}
// 	print_tree(tree->left, depth + 1);
// }