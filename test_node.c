// AI generated, no idea whats happening inside
#include "minishell.h"
#include "execution/exec.h"
#include <string.h>   // strcmp
#include <stdarg.h>
#include <errno.h>

// small dup helpers (use your libft versions if you prefer)
static char **dup_vec_filtered(int keep_count) {
    char **out = ft_calloc(keep_count + 1, sizeof(char *));
    if (!out) return NULL;
    return out; // callers fill it; null-terminated by calloc
}

static char **one_file_array_dup(const char *file) {
    if (!file) return NULL;
    char **arr = ft_calloc(2, sizeof(char *));
    if (!arr) return NULL;
    arr[0] = ft_strdup(file);
    if (!arr[0]) { free(arr); return NULL; }
    return arr;
}

/*
** mock_node_from_argv:
**  - Consumes (frees) the incoming argv + its strings
**  - Builds a node with:
**      node->argv     = cleaned argv (no redir tokens)
**      node->infile   = ["file", NULL] if last "< file" present
**      node->outfile  = ["file", NULL] if last ">" or ">>" present
**      node->append   = 1 if last was ">>", else 0
*/
static t_ast *mock_node_from_argv(char **argv)
{
    t_ast  *node = NULL;
    int     i, keep_count = 0;
    int     last_in = -1, last_out = -1, last_out_is_append = 0;
    char   *infile = NULL, *outfile = NULL;
    char  **argv_clean = NULL;

    if (!argv) return NULL;

    /* 1) Find last < and last > / >> */
    for (i = 0; argv[i]; ++i) {
        if (!strcmp(argv[i], "<") && argv[i+1]) {
            last_in = i;
        } else if ((!strcmp(argv[i], ">") || !strcmp(argv[i], ">>")) && argv[i+1]) {
            last_out = i;
            last_out_is_append = (argv[i][1] == '>');
        }
    }

    /* 2) Extract filenames (duplicate), count kept args (non-redir tokens) */
    for (i = 0; argv[i]; ++i) {
        if (!strcmp(argv[i], "<") && argv[i+1]) { i++; continue; }
        if ((!strcmp(argv[i], ">") || !strcmp(argv[i], ">>")) && argv[i+1]) { i++; continue; }
        keep_count++;
    }

    if (last_in >= 0)   infile  = ft_strdup(argv[last_in + 1]);
    if (last_out >= 0)  outfile = ft_strdup(argv[last_out + 1]);

    /* 3) Build cleaned argv */
    argv_clean = dup_vec_filtered(keep_count);
    if (!argv_clean) goto oom;

    int k = 0;
    for (i = 0; argv[i]; ++i) {
        if (!strcmp(argv[i], "<") && argv[i+1]) { i++; continue; }
        if ((!strcmp(argv[i], ">") || !strcmp(argv[i], ">>")) && argv[i+1]) { i++; continue; }
        argv_clean[k] = ft_strdup(argv[i]);
        if (!argv_clean[k]) goto oom;
        k++;
    }
    /* argv_clean[k] already NULL due to calloc */

    /* 4) Free original argv (and its strings) to avoid leaks */
    for (i = 0; argv[i]; ++i) free(argv[i]);
    free(argv);

    /* 5) Assemble node */
    node = ft_calloc(1, sizeof(*node));
    if (!node) goto oom;

    node->type    = NODE_COMMAND;
    node->argv    = argv_clean;              // owns
    node->infile  = infile  ? one_file_array_dup(infile)  : NULL;  // owns
    node->outfile = outfile ? one_file_array_dup(outfile) : NULL;  // owns
    node->append  = last_out_is_append ? 1 : 0;
    node->left    = NULL;
    node->right   = NULL;

    free(infile);
    free(outfile);
    return node;

oom:
    if (argv_clean) {
        for (int j = 0; argv_clean[j]; ++j) free(argv_clean[j]);
        free(argv_clean);
    }
    if (infile)  free(infile);
    if (outfile) free(outfile);
    /* also free original argv if we still own it */
    if (argv) {
        for (i = 0; argv[i]; ++i) free(argv[i]);
        free(argv);
    }
    return NULL;
}
