// AI generated - no idea whats happening here
#include "minishell.h"
#include "execution/exec.h"
#include <string.h>
#include <errno.h>

static char	**dup_vec_filtered(int keep_count)
{
	char	**out;

	out = ft_calloc(keep_count + 1, sizeof(char *));
	if (!out)
		return (NULL);
	return (out);
}

static char	**one_file_array_dup(const char *file)
{
	char	**arr;

	if (!file)
		return (NULL);
	arr = ft_calloc(2, sizeof(char *));
	if (!arr)
		return (NULL);
	arr[0] = ft_strdup(file);
	if (!arr[0])
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}

/*
** mock_node_from_argv:
**  - Consumes (frees) the incoming argv + its strings
**  - Builds a NODE_COMMAND with:
**      node->argv     = cleaned argv (no <,>,>> tokens)
**      node->infile   = ["file", NULL] if last "< file" present
**      node->outfile  = ["file", NULL] if last ">" or ">>" present
**      node->append   = 1 if last was ">>", else 0
*/
static t_ast	*mock_node_from_argv(char **argv)
{
	t_ast	*node;
	int		i;
	int		keep;
	int		last_in;
	int		last_in_is_heredoc;
	int		last_out;
	int		last_out_is_append;
	char	*infile;
	char	*outfile;
	char	*heredoc_delim;
	char	**argv_clean;
	int		k;

	if (!argv)
		return (NULL);
	last_in = -1;
	last_in_is_heredoc = 0;
	last_out = -1;
	last_out_is_append = 0;
	i = 0;
	while (argv[i])
	{
		if ((strcmp(argv[i], "<") == 0 || strcmp(argv[i], "<<") == 0)
			&& argv[i + 1])
		{
			last_in = i;
			last_in_is_heredoc = (argv[i][1] == '<');
		}
		else if (strncmp(argv[i], "<<", 2) == 0 && argv[i][2] != '\0')
		{
			last_in = i;
			last_in_is_heredoc = 1;
		}
		else if ((strcmp(argv[i], ">") == 0 || strcmp(argv[i], ">>") == 0)
			&& argv[i + 1])
		{
			last_out = i;
			if (argv[i][1] == '>')
				last_out_is_append = 1;
		}
		i++;
	}
	keep = 0;
	i = 0;
	while (argv[i])
	{
		if ((strcmp(argv[i], "<") == 0 || strcmp(argv[i], "<<") == 0)
			&& argv[i + 1])
			i++;
		else if (strncmp(argv[i], "<<", 2) == 0 && argv[i][2] != '\0')
			; /* skip "<<X" token */
		else if ((strcmp(argv[i], ">") == 0 || strcmp(argv[i], ">>") == 0)
			&& argv[i + 1])
			i++;
		else
			keep++;
		i++;
	}
	infile = NULL;
	outfile = NULL;
	heredoc_delim = NULL;
	if (last_in >= 0)
	{
		if (last_in_is_heredoc)
		{
			if (strcmp(argv[last_in], "<<") == 0 && argv[last_in + 1])
				heredoc_delim = ft_strdup(argv[last_in + 1]);
			else if (strncmp(argv[last_in], "<<", 2) == 0)
				heredoc_delim = ft_strdup(argv[last_in] + 2);
		}
		else if (argv[last_in + 1])
			infile = ft_strdup(argv[last_in + 1]);
	}
	if (last_out >= 0 && argv[last_out + 1])
		outfile = ft_strdup(argv[last_out + 1]);
	argv_clean = dup_vec_filtered(keep);
	if (!argv_clean)
		return (NULL);
	i = 0;
	k = 0;
	while (argv[i])
	{
		if ((strcmp(argv[i], "<") == 0 || strcmp(argv[i], "<<") == 0)
			&& argv[i + 1])
			i++;
		else if (strncmp(argv[i], "<<", 2) == 0 && argv[i][2] != '\0')
			; /* skip "<<X" */
		else if ((strcmp(argv[i], ">") == 0 || strcmp(argv[i], ">>") == 0)
			&& argv[i + 1])
			i++;
		else
		{
			argv_clean[k] = ft_strdup(argv[i]);
			k++;
		}
		i++;
	}
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (NULL);
	node->type = NODE_COMMAND;
	node->argv = argv_clean;
	if (infile)
		node->infile = one_file_array_dup(infile);
	if (outfile)
		node->outfile = one_file_array_dup(outfile);
	node->append = last_out_is_append;
	node->left = NULL;
	node->right = NULL;
	if (heredoc_delim)
	{
		node->heredoc = 1;
		node->heredoc_tmp = heredoc_delim;
	}
	else
	{
		node->heredoc = 0;
		node->heredoc_tmp = NULL;
	}
	node->heredoc_fd = -1;
	free(infile);
	free(outfile);
	return (node);
}


static int	find_pipe_index(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (strcmp(argv[i], "|") == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	**dup_segment(char **argv, int start, int end)
{
	int		len;
	int		i;
	char	**seg;

	len = end - start;
	seg = ft_calloc(len + 1, sizeof(char *));
	if (!seg)
		return (NULL);
	i = 0;
	while (i < len)
	{
		seg[i] = ft_strdup(argv[start + i]);
		if (!seg[i])
			return (seg);
		i++;
	}
	return (seg);
}

/* frees original argv (and its strings) */
static void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

/* Builds either:
**  - a NODE_COMMAND (no pipe)
**  - a NODE_PIPE with left/right NODE_COMMAND (single '|')
*/
static t_ast	*build_mock_ast_from_argv(char **argv)
{
	int		pipe_idx;
	int		i;
	char	**left_argv;
	char	**right_argv;
	t_ast	*left;
	t_ast	*right;
	t_ast	*pipe_node;

	if (!argv)
		return (NULL);
	pipe_idx = find_pipe_index(argv);
	if (pipe_idx < 0)
		return (mock_node_from_argv(argv));
	/* build left/right argv segments */
	left_argv = dup_segment(argv, 0, pipe_idx);
	i = 0;
	while (argv[i])
		i++;
	right_argv = dup_segment(argv, pipe_idx + 1, i);
	free_argv(argv);
	left = mock_node_from_argv(left_argv);
	right = mock_node_from_argv(right_argv);
	if (!left || !right)
		return (NULL);
	pipe_node = ft_calloc(1, sizeof(*pipe_node));
	if (!pipe_node)
		return (NULL);
	pipe_node->type = NODE_PIPE;
	pipe_node->left = left;
	pipe_node->right = right;
	pipe_node->heredoc_fd = -1;
	return (pipe_node);
}
