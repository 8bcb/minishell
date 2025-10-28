#include "./exec.h"

int exec_command(t_ast *cmd, t_env *env)
{
    if (!cmd || !cmd -> argv || !cmd -> argv[0])
    {
        return 0;
    }

    if (is_builtin(cmd -> argv[0]) == 1)
    {
        return exec_builtin(cmd, env);
    }
}

int    is_builtin(char *cmd_name)
{
    if (ft_strcmp(cmd_name, "echo") == 0)
    {
        return 1;
    }
    return 0;
}