#include "../minishell.h"
#include "env_utils.h"

char *get_env_key(t_env_expand *ex, int *len)
{
    int     k;
    char    *var_key;

    k = ex->i + 1;
    while (ex->rl[k])
    {
        if (is_separator(ex->rl[k]) || is_whitespace(ex->rl[k]) 
            || ex->rl[k] == 34 || ex->rl[k] == 39)
            break;
        (*len)++;
        k++;
    }
    if (*len == 0)
        return (NULL);
    var_key = ft_substr(ex->rl, ex->i + 1, *len);
    if (!var_key)
        return (NULL);
    ex->i += *len + 1;
    return var_key;
}

int expand(t_env_expand *ex)
{
    int     k;
    char    *var_name;
    char    *var_value;
    t_env   *tmp;

    k = 0;
    var_value = NULL;
    tmp = ex->env;
    var_name = get_env_key(ex, &k);
    if (!var_name)
        return (1);
    while (tmp)
    {
        if (ft_strncmp(var_name, tmp->key, k) == 0 && tmp->key[k] == '\0')
        {
            var_value = tmp->value;
            break;
        }
        tmp = tmp->next;
    }
    free(var_name);
    if (!var_value)
        return (1);
    k = 0;
    while (var_value[k]) {
        (ex->res)[ex->j] = var_value[k];
        k++;
        (ex->j)++;
    }
    free(var_value);
    return (0);
}

char    *expand_variables(char *rl, t_env *env)
{
    int             singleQuote;
    t_env_expand    exp;

    singleQuote = 0;
    exp.i = 0;
    exp.j = 0;
    exp.rl = rl;
    exp.env = env;
    exp.res = ft_calloc(ft_strlen(rl) + 1000, sizeof(char));
    if (!exp.res)
        return (NULL);
    while (rl[exp.i])
    {
        if (rl[exp.i] == '$' && singleQuote == 0)
            expand(&exp);
        else
        {
            if (rl[exp.i] == 39) {
                if (singleQuote == 1)
                    singleQuote = 0;
                else
                    singleQuote = 1;
            }
            exp.res[(exp.j)++] = rl[(exp.i)++];
        }
    }
    return exp.res;
}